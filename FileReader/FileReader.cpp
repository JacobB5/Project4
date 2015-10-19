#include <iostream>
#include <fstream>
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"
using namespace std;
using namespace KP_FileReaderClass;

//TODO Fill this in
FileReader::FileReader(){
	filecontents="";
}


int FileReader::getFileContents(const std::string filename, std::string &contents)
{
	int returnCode=ReadTheWholeFile(filename);
	if (returnCode==SUCCEEDED){
		contents=filecontents;
	}
	return returnCode;	
}

int FileReader::ReadTheWholeFile(const std::string &filename)
{
	ifstream myInputFile(filename);

	if (myInputFile.good())
	{
		try
		{

			myInputFile.open(filename.c_str(), ios::in);

			if (myInputFile.is_open()){				
				string line;

				while (!myInputFile.eof()) {
					getline(myInputFile, line);
					filecontents+=line;
				}
				try{
					myInputFile.close();
					return SUCCEEDED;
				}
				catch(exception& e)
				{
					cout<<"Exception occured: "<< e.what() << endl;
					return COULD_NOT_CLOSE_FILE;
				}
			}

		}
		catch (exception& e)
		{

			cout<<"Exception occured: "<< e.what() << endl;
			return COULD_NOT_OPEN_FILE;
		}
	}
	else return COULD_NOT_OPEN_FILE;
}

