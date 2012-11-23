#ifndef _SONGS_CPP_
#define _SONGS_CPP_

#include "Songs.h"
#include <algorithm>

std::string * Songs::toString()
{
	return &dataString;
}

song * Songs::toStruct()
{
	return &data;
}

// char * Songs::toChar()
// {
// 	char * s;
// 	s = new char[dataString.size()];
// 	
// 	strcpy(s, dataString.c_str());
// 	
// 	return s;
// }

// int Songs::charSize()
// {
// 	return dataString.size();
// }

void Songs::setData(std::string *dataInput)
{
		
	dataString = dataInput->substr(0,-1);
		
	std::string substring;
		
	substring = getParent(dataInput);
	stripString(&substring, "[],");
	
	// std::cout << "OUTPUT>"<< substring << std::endl;
	
	std::istringstream s(substring);
		
	s >> data.id;
	
	substring = getParent(dataInput);
	stripString(&substring, "[]");
	
	data.Title = substring;
	
	substring = getParent(dataInput);
	stripString(&substring, "[]");
		
	data.Artists = substring;
	// data.Artists.append("\0");
		
	substring = getParent(dataInput);
	
	// std::cout << substring << std::endl;
	
	stripString(&substring, "[]");
	
	// std::cout << substring << std::endl;
		
	int i;
		
	std::string subSubString;
	std::string token;
	
	data.rCount = 0;
	
	for(i = 0; ((int)substring.find("("))  != -1; i++)
	{
		// std::cout << "INPUT>" << substring << std::endl;
		
		subSubString = getChild(&substring);
		
		// std::cout << "OUTPUT>"<< subSubString << std::endl;
		// std::cout << "STRLEN>" << substring.size() << std::endl;
		// std::cout << "MASTER>" << substring << std::endl;
		
		stripString(&subSubString, "()");
		
		// std::cout << "SEARCH>" << (((int)substring.find("("))  == -1) << std::endl;
		
		// std::cout << "CLEANED>" << subSubString << std::endl;
		
		//std::cout << std::count(substring.begin(), substring.end(), ')') << std::endl;
		
		//std::cout << substring << std::endl;
		
		// std::cout << subSubString << std::endl;
			
		token = getCSV(&subSubString);
		
		// std::cout << "TOKEN1>" << token << std::endl;
		// std::cout << "OUTPUT>"<< subSubString << std::endl;
		
		data.ratings[i].User = token;
		
		token = getCSV(&subSubString);
		
		// std::cout << "TOKEN2>" << token << std::endl;
		// std::cout << "OUTPUT>"<< subSubString << std::endl;
		
		std::istringstream r(token);
		
		// std::cout << "INT>" << integer << std::endl;
		
		r >> data.ratings[i].rating;
		
		data.rCount++;
	}
}

int Songs::getJustID(std::string * inputString)
{
	std::string substring;
	int ID;
		
	substring = getParent(inputString,0);
	stripString(&substring, "[],");
	
	// std::cout << "OUTPUT>"<< substring << std::endl;
	
	std::istringstream s(substring);
		
	s >> ID;
	
	return ID;
}

std::string Songs::getChild(std::string *inputString)
{
	int startPos, length;
	std::string substring;
	
	// std::cout << "INPUT>" << *inputString << std::endl;
	
	startPos = inputString->find("(");
	length = inputString->find(")");
	
	substring = inputString->substr(startPos, length - startPos + 1);
	
	// std::cout << "OUTPUT>" << substring << std::endl;
		
	// inputString->erase(0, length + startPos);
	inputString->erase(startPos, length - startPos + 1);
	
	// std::cout << "STRLEN>" << inputString->size() << std::endl;
		
	return substring;

}

std::string Songs::getParent(std::string *inputString)
{
	int startPos, length;
	std::string substring;
	
	startPos = inputString->find("[");
	length = inputString->find("]");
		
	substring = inputString->substr(startPos, length);
		
	inputString->erase(0, startPos + length);
		
	return substring;
}

std::string Songs::getParent(std::string *inputString, bool del = 0)
{
	int startPos, length;
	std::string substring;
	
	startPos = inputString->find("[");
	length = inputString->find("]");
		
	substring = inputString->substr(startPos, length);
	
	if(del)
		inputString->erase(0, startPos + length);
		
	return substring;
}

std::string Songs::getCSV(std::string *inputString)
{
	int endPos;
	std::string substring;
		
	endPos = inputString->find(",");
		
	substring = inputString->substr(0, endPos);
		
	inputString->erase(0, endPos + 1);
		
	return substring;
}

void Songs::stripString(std::string *inputString, const char * chars)
{
	//char chars[] = "[]";
	   
	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		inputString->erase (std::remove(inputString->begin(), inputString->end(), chars[i]), inputString->end());
	}
	
	//return *inputString;
}

#endif
