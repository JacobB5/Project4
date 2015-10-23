//============================================================================
// Name        : Proj4_Test.cpp
// Author      : Nigel Armstrong and Jacob Bechtel
// Version     : 21 October 2015 0.01a
// Copyright   : Creative Commons, non-commercial, attribution
// Description : Painful reader
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "..\Include\FileReader.h"	//relative path, from PWD, go up one, then down into Include to find FileReader.h
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"
#include "..\Include\stringparserclass.h"

void convertStringtoCharPointer(std::string myString, char* &myPointer);

void outputvectorrow(std::string i) {
	std::cout << i << std::endl;

}

void foreach(std::vector<std::string> myVector) {
	std::for_each(myVector.begin(), myVector.end(), outputvectorrow);
}

int main() {
	std::vector<std::string> taggedText;
	//TODO open file, if not there ask for a different file or exit
	KP_FileReaderClass::FileReader reader;
	std::string contents = "";
	int outcome;
	outcome = reader.getFileContents(TEST_FILE_NAME, contents);
	while (outcome != SUCCEEDED) {
		std::string s;
		std::cout << "Please enter a filename to read in or 'X' to exit: ";
		std::cin.clear();
		std::cin >> s;
		if (s == "X")
		{
			outcome = USER_CHOSE_TO_EXIT;
		}
		else
		{
			outcome = reader.getFileContents(s, contents);
		}
	}

	if (outcome == SUCCEEDED) {
		//got file data, this is a bogus time and memory wasting step
		//whose sole purpose is to provide a way to pass
		//in a non const pointer to getDataBetweenTags(..) without casting
		/*vector<char> myLine;
		std::copy(filecontents.begin(), filecontents.end(), back_inserter(myLine));*/
		char *myPointer = new char[];
		convertStringtoCharPointer(contents, myPointer);

		//TODO  create an instance of the stringparser
		KP_StringParserClass::StringParserClass myParser;

		//TODO set the tags
		myParser.setTags(START_TAG, END_TAG);

		//TODO pull out the data
		myParser.getDataBetweenTags(myPointer, taggedText);

		//Lets delete memory we declared with new
		delete[] myPointer;

		//TODO  write to file and to screen
		std::ofstream myOutputFile;
		myOutputFile.open(OUTPUTFILENAME.c_str(), std::ios::out);
		foreach(taggedText);
		for (std::string i : taggedText)
			myOutputFile << i << std::endl;
	}
}

void convertStringtoCharPointer(std::string myString, char* &myPointer) {
	//Shows how to convert a string to a char pointer

	int len = myString.length();
	int lenPlusNull = len + 1; //add one for terminating null
	if (myPointer) {
		delete[] myPointer;
		myPointer = 0;
	}

	myPointer = new char[lenPlusNull];
	//set memory aside and write to 0's which also places a terminating null
	memset(myPointer, 0, lenPlusNull*sizeof(char));

	//Copy from the string to p
	myString.copy(myPointer, len, 0);
	//p now has a copy of the string in myString

	////Iterate over the pointer and set all values to 'a'
	//for(int i=0;i<len;i++)
	//	*(p+1)='a';

	/*if(p){
	delete[] p;
	p=0;
	}*/
}



