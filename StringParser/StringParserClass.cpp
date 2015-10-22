
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

	StringParserClass::StringParserClass(void)
	{
		pStartTag=0;
		pEndTag=0;
		areTagsSet=false;
		lastError=ERROR_NO_ERROR;
	}
	
	StringParserClass::~StringParserClass(void)
	{

	}

	int StringParserClass::getLastError()
	{
		int tempError=lastError;
		lastError=ERROR_NO_ERROR;
		return tempError;
	}

	bool StringParserClass::setTags(const char *pStartTag, const char *pEndTag)
	{
		if ((pStartTag!=NULL) && (pEndTag!=NULL))
		{		
			StringParserClass::pStartTag = (char*) pStartTag;
			StringParserClass::pEndTag = (char*) pEndTag;
			areTagsSet=true;
		}
		else
		{
			areTagsSet = false;
			lastError = ERROR_TAGS_NULL;

		}
		return areTagsSet;
	}

	bool getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector)
	{
		bool endSearch=false;
		string result="";
		char *start=pDataToSearchThru;
		char *end;
		int tagLength=0;

		if (!pDataToSearchThru){
			lastError = ERROR_DATA_NULL;
			return false;
		}
		else{
			if(!areTagsSet){
				return false;
			}
			else{
				//DO NOT INCLUDE THE TAGS THEMSELVES
				// USE strstr to check
				while (!endSearch){
					tagLength=strlen(pStartTag);
					start=strstr(start, pStartTag);
					if (!start){
						endSearch=true;
						return false;
					}
					else{
						start=start+(tagLength*sizeof(char));
						end=strstr(start, pEndTag);
						if(!end){
							endSearch=true;
							return false;
						}
						else{
							std::string target="";
							for (int i=0; start!=end;i++){
								target+=*start;
								start+=sizeof(char);
							}
							myVector.push_back(target);
							end=0;
						}
					}

				}
				return true;

			}
		}


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
	void convertStringtoCharPointer(){
		//Shows how to convert a string to a char pointer
		std::string myString="12345";
		int len = myString.length();
		int lenPlusNull=len+1; //add one for terminating null
		char *p=new char[lenPlusNull];
		//set memory aside and write to 0's which also places a terminating null
		memset(p,0,lenPlusNull*sizeof(char));

		//Copy from the string to p, 5 chars
		myString.copy(p,len,0);
		//p now has a copy of the string in myString

		//Iterate over the pointer and set all values to 'a'
		for(int i=0;i<len;i++)
			*(p+1)='a';

		if(p){
			delete[] p;
			p=0;
		}
	}


	//A simple search for a single item
	void charBasedStringComparison(char* p){

		if(!p){
			return;
		}

		//how long in tag
		int iten_P=strlen(p);

		char myString[] = "01234456";
		char *pinc = &myString[0];

		int iLen_MyString = strlen(pinc)/sizeof(char);

		int compare=SUCCEEDED;

		for(int ctr =0;ctr<iLen_MyString;ctr++){
			if (*p == *(pinc + ctr)){
				//Compare function start at p, go through to (pinc+ctr), but stop after iLen_p chars)
				compare = memcmp(p,(pinc+ctr),iten_P);
				if (compare == SUCCEEDED){
					std::cout<<"Found it"<<endl;
					return;
				}
			}

		}
	}

}