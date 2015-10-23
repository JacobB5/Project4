// Author Jacob Bechtel
// Author Nigel Armstrong
// Version 23 OCT 2015

#include <string>
#include "..\Include\stringparserClass.h"
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"

using namespace std;
namespace KP_StringParserClass
{
	//TODO Fill this in
	char	*pStartTag;
	char	*pEndTag;
	bool	areTagsSet;
	int		lastError;

	/*
	Constructor
	*/
	StringParserClass::StringParserClass(void)
	{
		pStartTag = 0;
		pEndTag = 0;
		areTagsSet = false;
		lastError = ERROR_NO_ERROR;
	}

	/*
	Destructor
	*/
	StringParserClass::~StringParserClass(void)
	{

	}

	/*
	return the last error from the class and clear it.
	*/
	int StringParserClass::getLastError()
	{
		int tempError = lastError;
		lastError = ERROR_NO_ERROR;
		return tempError;
	}

	/*
	Sets the start and end tags if they are valid pointers
	if the tags are bad, sets lastError
	*/
	bool StringParserClass::setTags(const char *pStartTag, const char *pEndTag)
	{
		if ((pStartTag != NULL) && (pEndTag != NULL))
		{
			StringParserClass::pStartTag = (char*)pStartTag;
			StringParserClass::pEndTag = (char*)pEndTag;
			areTagsSet = true;
		}
		else
		{
			areTagsSet = false;
			lastError = ERROR_TAGS_NULL;

		}
		return areTagsSet;
	}

	/*
	gets the data from the string at the char pointer. Puts the data in myVector
	*/
	bool StringParserClass::getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector)
	{
		bool endSearch = false;
		string result = "";
		char *start = pDataToSearchThru;
		char *end;
		int startTagLength = 0;

		//Check for null pointer
		if (!pDataToSearchThru) {
			lastError = ERROR_DATA_NULL;
			std::cout << "No data to search through for tags" << std::endl;
			return false;
		}

		//Make sure we have vaild tags
		if (!areTagsSet) {
			lastError = ERROR_TAGS_NULL;
			std::cout << "Tags are not set" << std::endl;
			return false;
		}
		//DO NOT INCLUDE THE TAGS THEMSELVES
		// USE strstr to check
		// Until we are ready to stop searching
		// In actuality we loop until break.
		while (!endSearch) {
			startTagLength = strlen(pStartTag);
			start = strstr(start, pStartTag);
			//start is now set to the start of startTag if found, otherwise null
			if (!start) {
				//We didn't find the start tag
				//This happend at the end of the stirng
				std::cout << "Start was set to null in get data between tags" << std::endl;
				endSearch = true;
				break;
			}
			//Move the pointer of the start of the string past the start tag
			start = start + (startTagLength*sizeof(char));
			//Search for the end tag
			end = strstr(start, pEndTag);
			if (!end) {
				//Found a start tag, but then no end tag.
				endSearch = true;
				return false; //This returns false if we find a start tag not followed by an end tag.
			}
			else {
				//The following two lines of code can replace the for loop if desired
				//std::string target = std::string(start, end - start);
				//start = end + strlen(pEndTag);

				//Copy the cstring to a std string.
				std::string target = "";
				for (int i = 0; start != end; i++) {
					target += *start;
					start += sizeof(char);
				}
				myVector.push_back(target);
				end = 0;
			}


		}
		if (myVector.size() == 0) {
			//Didn't find any tags
			return false;
		}
		return true;
	}

	//bool findTag(char *pTagToLookFor, char *&pStart, char *&pEnd)
	//{
	//	return true;
	//}
	//
	//void cleanup(){
	//	pStartTag=0;
	//	pEndTag=0;
	//	areTagsSet=false;
	//	lastError=ERROR_NO_ERROR;
	//}



	//Example
	void convertStringtoCharPointer() {
		//Shows how to convert a string to a char pointer
		std::string myString = "12345";
		int len = myString.length();
		int lenPlusNull = len + 1; //add one for terminating null
		char *p = new char[lenPlusNull];
		//set memory aside and write to 0's which also places a terminating null
		memset(p, 0, lenPlusNull*sizeof(char));

		//Copy from the string to p, 5 chars
		myString.copy(p, len, 0);
		//p now has a copy of the string in myString

		//Iterate over the pointer and set all values to 'a'
		for (int i = 0; i < len; i++)
			*(p + 1) = 'a';

		if (p) {
			delete[] p;
			p = 0;
		}
	}


	//A simple search for a single item
	void charBasedStringComparison(char* p) {

		if (!p) {
			return;
		}

		//how long in tag
		int iten_P = strlen(p);

		char myString[] = "01234456";
		char *pinc = &myString[0];

		int iLen_MyString = strlen(pinc) / sizeof(char);

		int compare = SUCCEEDED;

		for (int ctr = 0; ctr < iLen_MyString; ctr++) {
			if (*p == *(pinc + ctr)) {
				//Compare function start at p, go through to (pinc+ctr), but stop after iLen_p chars)
				compare = memcmp(p, (pinc + ctr), iten_P);
				if (compare == SUCCEEDED) {
					std::cout << "Found it" << endl;
					return;
				}
			}

		}
	}

}
