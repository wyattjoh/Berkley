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
int Songs::charSize()
{
	return dataString.size();
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
	std::string token;
	
	data.rCount = 0;
	
	for(i = 0; substring.size() > 0; i++)
	{
		subSubString = getChild(&substring);
			
		token = getCSV(&subSubString);
			
		data.ratings[i].User = token;
			
		token = getCSV(&subSubString);
			
		std::istringstream r(token);
			
		r >> data.ratings[i].rating;
		
		data.rCount++;
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
