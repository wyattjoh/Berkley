// Berkeley DB Example
// This program creates/uses a hash file to hold (id/student_name) of students 
// gcc -lm -ldb -I /usr/local/include -L /usr/local/lib -O bdb_sample.c

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>

// Include Classes
#include "class/Berkley.h"
#include "class/Songs.h"

// Include Structs
#include "struct/song.h"

// Include Loader
#include "class/Loader.h"

#define STDID_LEN 5
#define NAME_LEN 50

int main() 
{	
	Berkley myDB("../data/A4Database.db");
	
	// Load the contents of the text file into the database
	BerkleyLoader::loader(&myDB,"../data/A4TestData.txt");
	
	Songs mySong;
	int sfRet;
	char id[10];
	
	for (;;)
	{
		printf("\nEnter ID (0 to exit): "); 
		sfRet = scanf("%s",id);
		
		if (id[0]=='0')
			break;
		
		if(myDB.get(id))
		{
			// std::cout << "Found: " << myDB.getData() << std::endl;
								 	
			std::string songData = myDB.getData();
									
			mySong.setData(&songData);
			song * mySongStruct = mySong.toStruct();
			
			std::cout << "--------------------------------" << std::endl;
			std::cout << "Title: " << mySongStruct->Title << std::endl;
			std::cout << "Artists: " << mySongStruct->Artists << std::endl;
			
			for(int i = 0; i<mySongStruct->rCount; i++)
			{
				std::cout << "Rating " << mySongStruct->ratings[i].User << " " << mySongStruct->ratings[i].rating << std::endl;
			}
			
			std::cout << "--------------------------------" << std::endl;
		}
		else
		{
			std::cout << "Not Found" << std::endl;
		}
	}
	
	return 0;
} 
 