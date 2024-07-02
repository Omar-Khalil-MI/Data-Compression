#pragma once
#include <unordered_map>
#include <iostream>
#include <queue>
#include <fstream>
#include <iomanip>
#include <string>
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
	 Postcondition: HuffTree has been constructed with nodes from queue and
	 myRoot points to the tree root.
	 Note: It uses private auxiliary function mergeAux
	 ------------------------------------------------------------------------*/

	inline bool leafNode(const NodePointer& Node) const;
	/*------------------------------------------------------------------------
	 Checks if leaf node.

	 Precondition:  None.
	 Postcondition: Returns if lead node
	 ------------------------------------------------------------------------*/


	inline void calcFreq(const string& fileName, unordered_map<char, unsigned int>& freqMap);
	/*------------------------------------------------------------------------
	Calculate the frequency of all characters in a given file.

	 Precondition:  File exists and not empty.
	 Postcondition: Unordered map is returned with all characters
	 and their frequnecy
	 ------------------------------------------------------------------------*/

	inline void constructQueue(unordered_map<char, unsigned int>& freqMap);
	/*------------------------------------------------------------------------
	 <Enter Discription here>.

	 Precondition:  None.
	 Postcondition:
	 Note: the function will call private function merge.
	 ------------------------------------------------------------------------*/

	inline void generateCodes(NodePointer subtree, string code, unordered_map<char, string>& codeMap) const;
	/*------------------------------------------------------------------------
	 generate Huffman codes for each character

	 Precondition:  ....
	 Postcondition: Each character in the Huffman tree will have its equivalent
	 huffman code
	 ( Key ) stored in the codesMap.

	 ------------------------------------------------------------------------*/

	void reconstructTree(unordered_map<char, string>& codeMap);
	/*------------------------------------------------------------------------

	 Precondition:
	 Postcondition:
	 ------------------------------------------------------------------------*/

	inline void exportKey(const unordered_map<char, string>& keyMap, ofstream& filename) const;
	/*------------------------------------------------------------------------

	 Precondition:
	 Postcondition:
	 ------------------------------------------------------------------------*/

	inline void importKey(const string& filename);
	/*------------------------------------------------------------------------

	 Precondition:
	 Postcondition:
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
	 Encodes the unputFile and Writes the encoded text in the outputFile.

	 Precondition:  OutputFile exists and not empty.
	 Postcondition: The encoded text for the string will be written
	 to the file specified by outputFileName
	 ------------------------------------------------------------------------*/

	void decodeTextToFile(const string& inputFileName, const string& outputFileName);
	/*------------------------------------------------------------------------
	 Decodes  the inputFile and writes the decoded text in the outputFile.

	 Precondition:  OutputFile exists and not empty.
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
