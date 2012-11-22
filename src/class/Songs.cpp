#ifndef _SONGS_CPP_
#define _SONGS_CPP_

#include "Songs.h"

std::string * Songs::toString()
{
	return &dataString;
}

song * Songs::toStruct()
{
	return &data;
}

char * Songs::toChar()
{
	char * s;
	s = new char[dataString.size()];
	
	strcpy(s, dataString.c_str());
	
	return s;
}

void Songs::setData(std::string *dataInput)
{
		
	dataString = dataInput->substr(0,-1);
		
	std::string substring;
		
	substring = getParent(dataInput);
		
	std::istringstream s(substring);
		
	s >> data.id;
		
	data.Title = getParent(dataInput);
		
	data.Artists = getParent(dataInput);
		
	substring = getParent(dataInput);
		
	int i;
		
	std::string subSubString;
		
	for(i = 0; substring.size() > 0; i++)
	{
		data.rat[i] = getChild(&substring);
			
		subSubString = getCSV(&data.rat[i]);
			
		data.ratings[i].User = subSubString;
			
		subSubString = getCSV(&data.rat[i]);
			
		std::istringstream r(subSubString);
			
		r >> data.ratings[i].rating;
	}
}

std::string Songs::getParent(std::string *inputString)
{
	int startPos, length;
	std::string substring;
		
	startPos = inputString->find("[") + 1;
	length = inputString->find("]") - 1;
		
	substring = inputString->substr(startPos, length - 1);
		
	inputString->erase(0, startPos + length);
		
	return substring;
}

std::string Songs::getChild(std::string *inputString)
{
	int startPos, length;
	std::string substring;
		
	startPos = inputString->find("(") + 1;
	length = inputString->find(")");
		
	substring = inputString->substr(startPos, length - 1);
		
	inputString->erase(0, startPos + length+ 1);
		
	return substring;

}

std::string Songs::getCSV(std::string *inputString)
{
	int endPos;
	std::string substring;
		
	endPos = inputString->find(",");
		
	substring = inputString->substr(0, endPos - 1);
		
	inputString->erase(0, endPos + 1);
		
	return substring;
}

#endif
