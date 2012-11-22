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
	std::string * toString();
	song * toStruct();
	char * toChar();
	void setData(std::string *dataInput);
private:
	song data;
	std::string dataString;
	std::string getParent(std::string *inputString);
	std::string getChild(std::string *inputString);
	std::string getCSV(std::string *inputString);
};

#endif