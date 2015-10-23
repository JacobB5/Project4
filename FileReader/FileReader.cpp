// Author Jacob Bechtel
// Author Nigel Armstrong
// Version 23 OCT 2015
#include <iostream>
#include <fstream>
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"
using namespace std;
namespace KP_FileReaderClass {

	//TODO Fill this in
	/*
	constructor, initializes thes filecontents
	*/
	FileReader::FileReader() {
		filecontents = "";
	}

	/*
	destructor
	*/
	FileReader::~FileReader() {

	}

	/*
	Reads the entire file give by filename into the string contents
	*/
	int FileReader::getFileContents(const std::string filename, std::string &contents)
	{
		//Try to read the whole file
		int returnCode = ReadTheWholeFile(filename);
		if (returnCode == SUCCEEDED) {
			//If we read the file, then copy the contents to the output.
			contents = filecontents;
		}
		return returnCode;
	}

	/*
	Reads the file given by filename into the class variable filecontenets.
	Returns SUCCEEDED on good read, otherwise returns COULD_NOT_OPEN_FILE
	*/
	int FileReader::ReadTheWholeFile(const std::string &filename)
	{
		ifstream myInputFile;

		if (myInputFile.good())
		{
			//Try to open the file
			myInputFile.open(filename.c_str(), ios::in);

			//Make sure we opened the file
			if (myInputFile.is_open()) {
				string line;
				//Read every line in the file
				while (getline(myInputFile, line)) {
					filecontents += line;
				}
				//Close the file when we are done and return
				myInputFile.close();
				return SUCCEEDED;
			}

		}
		//We didn't succeed
		return COULD_NOT_OPEN_FILE;
	}

}
