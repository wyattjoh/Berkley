#ifndef _LOADER_CPP_
#define _LOADER_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>

// Include Classes
#include "Berkley.h"
#include "Songs.h"

// Include Structs
#include "../struct/song.h"

namespace BerkleyLoader
{
	void loader(Berkley *myDB, const char * dataFile)
	{
		std::ifstream file(dataFile);
	
		std::string line;
	
		std::cout << "Processing input text file...";
	
		//int count = 0;
	
		//while(getline(file, line) && count <= 30)
		while(getline(file, line))
		{
			//count++;
		
			//std::cout << "Line(" << line << ")" << std::endl;
		
			Songs *record = new Songs();
			(*record).setData(&line);
		
			song *rSong = (*record).toStruct();
		
			char index[33];
		
			sprintf(index, "%d", rSong->id);
		
			int charSize = (*record).charSize();
		
			std::string * songString = (*record).toString();
		
			char * s = new char[charSize + 1];
		
			std::copy(songString->begin(), songString->end(), s);
			s[songString->size()] = '\0';
		
			//strcpy(s, (*record).toString()->c_str());
		
			myDB->put(index, s);
		
			delete [] s;
			delete record;
		}
		
		file.close();
		
		std::cout << "done." << std::endl;
	}
}

#endif
