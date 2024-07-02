#pragma once
#include <unordered_map>
#include <iostream>
#include <queue>
#include <fstream>
#include <iomanip>
#include <string>
#include <core/core.hxx>

using namespace std;
class HuffTree
{
private:
	/***** Node class *****/
	class Node
	{
	public:
		char data;
		int freq;
		Node* left;
		Node* right;

		// Node constructors
		Node()
			: left(0), right(0)
		{}

		Node(char item, int frequency)
			: data(item), freq(frequency), left(0), right(0)
		{}

	};// end of class Node declaration

	typedef Node* NodePointer;

	/***** Data Members *****/
	NodePointer myRoot;

	/***** Function Members *****/

	inline void merge(priority_queue< pair<int, NodePointer> >& pq);
	/*------------------------------------------------------------------------
	 Merge all nodes from a priority queue into HuffTree.

	 Precondition:  None.
	 Postcondition: HuffTree is constructed with nodes from queue and
					myRoot points to the tree root.
	 ------------------------------------------------------------------------*/

	inline bool leafNode(const NodePointer& Node) const;
	/*------------------------------------------------------------------------
	 Checks if Node is a leaf node.

	 Precondition:  None.
	 Postcondition: None.
	 ------------------------------------------------------------------------*/

	inline void calcFreq(const string& fileName, unordered_map<char, unsigned int>& freqMap);
	/*------------------------------------------------------------------------
	 Calculate the frequency of all characters in a given file.

	 Precondition:  File exists and not empty,
					constructQueue() function is implemented.
	 Postcondition: Unordered map is returned with all characters
					and their frequnecy.
	 ------------------------------------------------------------------------*/

	inline void constructQueue(unordered_map<char, unsigned int>& freqMap);
	/*------------------------------------------------------------------------
	 Construct a priority queue with a pair of int and NodePointer.

	 Precondition:  merge() function is implemented.
	 Postcondition: None.
	 ------------------------------------------------------------------------*/

	inline void generateCodes(NodePointer subtree, string code, unordered_map<char, string>& codeMap) const;
	/*------------------------------------------------------------------------
	 Generate Huffman codes for each character in an unodered map.

	 Precondition:  Huffman tree is construcuted.
	 Postcondition: None.
	 ------------------------------------------------------------------------*/

	void reconstructTree(unordered_map<char, string>& codeMap);
	/*------------------------------------------------------------------------
	 Construct a Huffman tree from the codeMap.

	 Precondition:  None.
	 Postcondition: Huffman tree is constructed and myRoot
					points to the tree root.
	 ------------------------------------------------------------------------*/

	inline void exportKey(const unordered_map<char, string>& keyMap, ofstream& filename) const;
	/*------------------------------------------------------------------------
	 Export the key map into the encoded file.

	 Precondition:  None.
	 Postcondition: None.
	 ------------------------------------------------------------------------*/

	inline void importKey(const string& filename);
	/*------------------------------------------------------------------------
	 Import key from decoded file.

	 Precondition:  File has key to import,
					reconstructTree() function is implemeted.
	 Postcondition: None.
	 ------------------------------------------------------------------------*/

public:
	HuffTree();
	/*------------------------------------------------------------------------
	 Construct a HuffTree object.

	 Precondition:  None.
	 Postcondition: An empty HuffTree has been constructed.
	 -----------------------------------------------------------------------*/

	void encodeTextToFile(const string& inputFileName, const string& outputFileName);
	/*------------------------------------------------------------------------
	 Encodes the inputFile and writes the encoded text to the outputFile.

	 Precondition:  OutputFile & InputFile exists and are not empty,
					calcFreq() function is implemeted,
					generateCodes() function is implemeted,
					exportKey() function is implemeted.
	 Postcondition: The encoded text for the string will be written
					to the file specified by outputFileName
	 ------------------------------------------------------------------------*/

	void decodeTextToFile(const string& inputFileName, const string& outputFileName);
	/*------------------------------------------------------------------------
	 Decodes  the inputFile and writes the decoded text to the outputFile.

	 Precondition:  OutputFile & inputFile exists and not empty,
					importKey() function is implemeted.
	 Postcondition: The decoded text for the string will be written
					to the file specified by outputFileName
	 ------------------------------------------------------------------------*/

	float static calculateRatio(const string& uncompressed, const string& compressed);
	/*------------------------------------------------------------------------
	 Calculates the compression ratio.

	 Precondition: None
	 Postcondition: None
	 ------------------------------------------------------------------------*/

};//end of class declaration
