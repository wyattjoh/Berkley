// Name: Wyatt Johnson
// Unix: wyatt
// Date: Nov 23, 2012

#ifndef _SONGS_H_
#define _SONGS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

#include "../struct/song.h"

#include "Berkley.h"

class Songs {
public:
	std::string toString();
	song * toStruct();
	char * toChar();
	int charSize();
	void setData(std::string *dataInput);
	void updateUsersDB(Berkley * indexDB);
private:
	song data;
	std::string mine;
	std::string dataString;
	static std::string getParent(std::string *inputString);
	static std::string getChild(std::string *inputString);
	static std::string getCSV(std::string *inputString);
	static void stripString(std::string *inputString, const char * chars);
};

#endif