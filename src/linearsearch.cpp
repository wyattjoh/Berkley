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
#include "class/Linear.h"

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
	BerkleyLoader::loader(&myDB,"../data/a4data.txt");
	
	Songs SongA;
	Songs SongB;
	
	song * SongAStruct;
	song * SongBStruct;
	
	int sfRet;
	char id[10];
	std::string songData;
	
	for (;;)
	{
		printf("\nEnter ID for A(0 to exit): "); 
		sfRet = scanf("%s",id);
		
		if (id[0]=='0')
			break;
		
		if(myDB.get(id))
		{
			// std::cout << "Found: " << myDB.getData() << std::endl;
								 	
			songData = myDB.getData();
									
			SongA.setData(&songData);
			SongAStruct = SongA.toStruct();
		}
		else
		{
			std::cout << "Not Found" << std::endl;
			continue;
		}
		
		printf("\nEnter ID for A(0 to exit): "); 
		sfRet = scanf("%s",id);
		
		if (id[0]=='0')
			break;
		
		if(myDB.get(id))
		{
			// std::cout << "Found: " << myDB.getData() << std::endl;
								 	
			songData = myDB.getData();
									
			SongB.setData(&songData);
			SongBStruct = SongB.toStruct();
			
		}
		else
		{
			std::cout << "Not Found" << std::endl;
			continue;
		}
		
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Title: " << SongAStruct->Title << std::endl;
		std::cout << "Artists: " << SongAStruct->Artists << std::endl;
			
		// for(int i = 0; i<SongAStruct->rCount; i++)
		// {
		// 	std::cout << "Rating " << SongAStruct->ratings[i].User << " " << SongAStruct->ratings[i].rating << std::endl;
		// }
			
		std::cout << "--------------------------------" << std::endl;
		
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Title: " << SongBStruct->Title << std::endl;
		std::cout << "Artists: " << SongBStruct->Artists << std::endl;
			
		// for(int i = 0; i<SongBStruct->rCount; i++)
		// {
		// 	std::cout << "Rating " << SongBStruct->ratings[i].User << " " << SongBStruct->ratings[i].rating << std::endl;
		// }
		
		std::cout << "--------------------------------" << std::endl;
		
		double result = Linear::compare(SongAStruct, SongBStruct);
		
		std::cout << "Distance Calculation: " << result << std::endl;
	}
	
	return 0;
} 
 