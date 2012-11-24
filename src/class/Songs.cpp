#ifndef _SONGS_CPP_
#define _SONGS_CPP_

#include "Songs.h"
#include <algorithm>

std::string Songs::toString()
{
	
	// std::cout << "STRING>" << dataString << std::endl;
	
	return dataString;
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
		
	dataString = dataInput->substr(0,dataInput->length());
		
	std::string substring;
		
	substring = getParent(dataInput);
	stripString(&substring, "[],");
	
	// std::cout << "OUTPUT>"<< dataString << std::endl;
	
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

void Songs::updateUsersDB(Berkley * indexDB)
{
	// Itterate over all users that have rated said song with id saved
	for(int i = 0; i < data.rCount; i++)
	{
		// std::cout << data.ratings[i].User << ", ";
		
		// std::cout << "Looking up..." << std::endl;
		
		char * userChar = (char*)data.ratings[i].User.c_str();
		char songID[33];
		
		sprintf(songID, "%d,", data.id);
		
		if(indexDB->get(userChar))
		{
			std::string movData = indexDB->getData();
			movData.append(songID);
			
			char * newMovData = (char*)movData.c_str();
			
			indexDB->put(userChar, newMovData);
		}
		else
		{
			// std::cout << userChar << std::endl;
			indexDB->put(userChar, songID);
		}
		
		//std::string movs = indexDB.get;
	}
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
