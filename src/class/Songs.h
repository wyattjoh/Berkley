#ifndef _SONGS_H_
#define _SONGS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>

#include "../struct/song.h"

class Songs {
public:
	std::string *toString();
	song * toStruct();
	char * toChar();
	int charSize();
	void setData(std::string *dataInput);
private:
	song data;
	std::string dataString;
	static std::string getParent(std::string *inputString);
	static std::string getChild(std::string *inputString);
	static std::string getCSV(std::string *inputString);
	static void stripString(std::string *inputString, const char * chars);
};

#endif