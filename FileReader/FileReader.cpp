#include <iostream>
#include <fstream>
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"
using namespace std;
namespace KP_FileReaderClass {

	//TODO Fill this in
	FileReader::FileReader() {
		filecontents = "";
	}

	FileReader::~FileReader() {

	}


	int FileReader::getFileContents(const std::string filename, std::string &contents)
	{
		int returnCode = ReadTheWholeFile(filename);
		if (returnCode == SUCCEEDED) {
			contents = filecontents;
		}
		return returnCode;
	}

	int FileReader::ReadTheWholeFile(const std::string &filename)
	{
		ifstream myInputFile;

		if (myInputFile.good())
		{
			myInputFile.open(filename.c_str(), ios::in);

			if (myInputFile.is_open()) {
				string line;

				while (getline(myInputFile, line)) {
					filecontents += line;
				}
				myInputFile.close();
				return SUCCEEDED;
			}

		}
		
		return COULD_NOT_OPEN_FILE;
	}

}
