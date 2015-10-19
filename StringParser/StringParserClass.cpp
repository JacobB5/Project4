
#include <string>
#include "..\Include\stringparserClass.h"
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"

using namespace std;
using namespace KP_StringParserClass;

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
	lastError=SUCCEEDED;
}

int StringParserClass::getLastError()
{
	int tempError=lastError;
	lastError=SUCCEEDED;
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
	if(areTagsSet){

	}


}

bool findTag(char *pTagToLookFor, char *&pStart, char *&pEnd)
{
	
}

