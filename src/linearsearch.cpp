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
#include "struct/indexed.h"

// Include Loader
#include "class/Loader.h"

#define STDID_LEN 5
#define NAME_LEN 50

int main() 
{	
	Berkley myDB("../data/A4Database.db");
	
	// Load the contents of the text file into the database
	uint64_t numberofvalues = BerkleyLoader::loader(&myDB,"../data/a4data.txt");
	
	std::cout << "Proccessed " << numberofvalues << " entries." << std::endl;
	
	Songs SongA;
	Songs SongB;
	
	song * SongAStruct;
	song * SongBStruct;
	
	int sfRet;
	uint64_t quriedID;
	char id[33];
	
	double result;
	
	std::string songData;
	
	for (;;)
	{
		printf("\nEnter ID for A(0 to exit): "); 
		sfRet = scanf("%s",id);
		
		if (id[0]=='0' && sfRet)
			break;
		
		quriedID = atoi(id);
		
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
		
		indexed * MatchedEntries;
		MatchedEntries = new indexed[numberofvalues - 1];
		
		// printf("\nEnter ID for A(0 to exit): "); 
		// sfRet = scanf("%s",id);
		// 
		// if (id[0]=='0')
		// 	break;
		// 
		// if(myDB.get(id))
		// {
		// 	// std::cout << "Found: " << myDB.getData() << std::endl;
		// 						 	
		// 	songData = myDB.getData();
		// 							
		// 	SongB.setData(&songData);
		// 	SongBStruct = SongB.toStruct();
		// 	
		// }
		// else
		// {
		// 	std::cout << "Not Found" << std::endl;
		// 	continue;
		// }
		// 
		// result = Linear::compare(SongAStruct, SongBStruct);
		// 
		// std::cout << "Distance Calculation: " << result << std::endl;
		
		char searchID[33];
		int n;
		uint64_t valIndex = 0;
		
		for(uint64_t i = 1; i < numberofvalues; i++)
		{
			if( i == quriedID )
				continue;
			
			n = sprintf(searchID, "%"PRIu64, i);
			
			if(myDB.get(searchID))
			{
				//std::cout << "Found: " << myDB.getData() << std::endl;
								 	
				songData = myDB.getData();
									
				SongB.setData(&songData);
				SongBStruct = SongB.toStruct();
				
				result = Linear::compare(SongAStruct, SongBStruct);
				
				MatchedEntries[valIndex].index = i;
				MatchedEntries[valIndex].value = (double)result;
				
				valIndex++;
			}
			else
			{
				std::cout << "Not Found" << std::endl;
				continue;
			}
		}
		
		qsort(MatchedEntries, numberofvalues - 1, sizeof(MatchedEntries[0]), Linear::compare);
		
		std::cout << "Q:" << quriedID << std::endl;
		
		for(int in = 0; in < 100; in++)
		{
			std::cout << in << " - " << MatchedEntries[in].index << " - " << (double)MatchedEntries[in].value << std::endl;
		}
		
		delete [] MatchedEntries;
	}
	
	
	
	return 0;
} 
 