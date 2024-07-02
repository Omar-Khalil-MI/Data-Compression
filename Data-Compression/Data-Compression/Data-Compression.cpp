#include <iostream>
#include <string>
#include "HuffTree.h"
using namespace std;


int main()
{
	string const path = "../text/";
	string fileName;
	string inputFile = path;

	cout << "enter file to be encoded: ";
	cin >> fileName;
	inputFile.append(fileName).append(".txt");

	string outputFile = path;
	cout << "enter file to hold encoded text: ";
	cin >> fileName;
	outputFile.append(fileName).append(".txt");

	try {
		HuffTree h;
		h.encodeTextToFile(inputFile, outputFile);
		cout << "Compression ratio: " << HuffTree::calculateRatio(inputFile, outputFile) << endl;

		string outputfile2 = path;
		cout << "enter file to hold decoded text: ";
		cin >> fileName;
		outputfile2.append(fileName).append(".txt");
		h.decodeTextToFile(outputFile, outputfile2);
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}