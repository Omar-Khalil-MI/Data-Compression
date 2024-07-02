#include "HuffTree.h"
using namespace std;

HuffTree::HuffTree() : myRoot(0)
{
}

inline bool HuffTree::leafNode(const NodePointer& Node) const
{
	return ((Node->left == 0) && (Node->right == 0));
}

void HuffTree::encodeTextToFile(const string& inputFileName, const string& outputFileName)
{
	ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
		throw runtime_error("Unable to open input file!");


	ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
		throw runtime_error("Unable to open output file!");

	//Calculate frequencey and create the Huffman Tree
	unordered_map<char, unsigned int> freqMap;
	calcFreq(inputFileName, freqMap);

	//Generate the keymap by traversing the Huffman Tree
	unordered_map<char, string> keyMap;
	generateCodes(myRoot, "", keyMap);

	//Print the encoded data
	char ch;
	while (inputFile.get(ch)) {
		// Check if character has a Huffman code
		if (keyMap.find(ch) != keyMap.end())
			outputFile << keyMap[ch];
		else
			throw runtime_error("Could not compress file!");
	}
	//Print the key in the same file
	exportKey(keyMap, outputFile);

	inputFile.close();
	outputFile.close();
}

inline void HuffTree::calcFreq(const string& fileName, unordered_map<char, unsigned int>& freqMap)
{
	ifstream file(fileName);

	//Check if file exists or not empty
	if (!file.good())
		throw runtime_error("File does not exist!");
	if (file.peek() == ifstream::traits_type::eof())
		throw runtime_error("File is empty!");

	short ch;
	//Read each character in the file and update frequency in the map
	while ((ch = file.get()) != EOF)
		freqMap[ch]++;

	file.close();
	constructQueue(freqMap);
}

inline void HuffTree::constructQueue(unordered_map<char, unsigned int>& freqMap)
{
	priority_queue< pair<int, NodePointer> > pq;
	//Create new node and push in queue
	for (const auto& pair : freqMap) {
		NodePointer n = new Node(pair.first, pair.second);  //Insert Character, Frequency
		pq.push(make_pair(pair.second * -1, n));            //Insert key(freq*-1), Node
	}
	merge(pq);
}

inline void HuffTree::merge(priority_queue< pair<int, NodePointer> >& pq)
{
	//Construct HuffTree
	NodePointer left, right;
	while (pq.size() != 1)
	{
		left = pq.top().second;
		pq.pop();
		right = pq.top().second;
		pq.pop();

		NodePointer n = new Node(NULL, left->freq + right->freq);
		n->left = left;
		n->right = right;

		pq.push(make_pair(n->freq * -1, n));
	}
	//set HuffTree root to the remaining node in the queue 
	myRoot = pq.top().second;
}

inline void HuffTree::generateCodes(NodePointer subtree, string code, unordered_map<char, string>& codeMap) const
{
	if (leafNode(subtree)) {
		codeMap[subtree->data] = code;
		return;
	}
	// Traverse left child with '0'
	generateCodes(subtree->left, code + "0", codeMap);
	// Traverse right child with '1'
	generateCodes(subtree->right, code + "1", codeMap);
}

inline void HuffTree::exportKey(const unordered_map<char, string>& keyMap, ofstream& filename) const
{
	filename << endl << "/K";
	for (const auto& pair : keyMap) {
		filename << endl;
		if (pair.first == '\n')
			filename << "\\n";
		else filename << pair.first;
		filename << endl << pair.second;
	}
}

inline void HuffTree::importKey(const string& filename)
{
	unordered_map<char, string> keyMap;
	string chr, code;
	ifstream file(filename);

	do {
		getline(file, chr);
	} while (chr != "/K");

	while (getline(file, chr))
	{
		getline(file, code);
		if (chr == "\\n")
			chr = "\n";
		keyMap.insert(make_pair(chr[0], code));
	}
	reconstructTree(keyMap);
}

void HuffTree::reconstructTree(unordered_map<char, string>& codeMap) {
	myRoot = new Node();
	NodePointer curr;
	for (auto& pair : codeMap) {
		char character = pair.first;
		string code = pair.second;
		curr = myRoot;
		for (int i = 0; i < code.length(); i++) {
			if (code[i] == '0') {
				if (curr->left == nullptr)
					curr->left = new Node();
				curr = curr->left;
			}
			else if (code[i] == '1') {
				if (curr->right == nullptr)
					curr->right = new Node();
				curr = curr->right;
			}
		}
		curr->data = character;
	}
}

void HuffTree::decodeTextToFile(const string& inputFileName, const string& outputFileName)
{
	ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
		throw runtime_error("Unable to open input file");

	importKey(inputFileName);

	string encodedtxt, decodedtxt = "";
	inputFile >> encodedtxt;
	inputFile.close();

	NodePointer currentPointer = myRoot;
	for (int i = 0; i < encodedtxt.size(); i++) {
		if (encodedtxt[i] == '0')
			currentPointer = currentPointer->left;
		else
			currentPointer = currentPointer->right;
		// reached leaf node
		if (leafNode(currentPointer)) {
			decodedtxt += currentPointer->data;
			currentPointer = myRoot;
		}
	}

	ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
		throw runtime_error("Unable to open output file");

	outputFile << decodedtxt;
	outputFile.close();
}

float HuffTree::calculateRatio(const string& uncompressed, const string& compressed)
{
	ifstream decoded(uncompressed), encoded(compressed);

	int decSize = 0, encSize = 0;
	string line;

	//Count number of lines in each file
	while (getline(decoded, line))
		decSize += line.length();
	while (getline(encoded, line) && line != "/K")
		encSize += line.length();
	//Add '/K' size and the letters size with their encoding size
	encSize += 2 * 8;
	while (getline(encoded, line))
	{
		getline(encoded, line);
		encSize += line.length() + 8;
	}
	return float(decSize * 8) / encSize;
}
