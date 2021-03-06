// Name: Wyatt Johnson
// Unix: wyatt
// Date: Nov 23, 2012

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <time.h>

// Include Classes
#include "class/Berkley.h"
#include "class/Songs.h"
#include "class/Linear.h"

// Include Structs
#include "struct/song.h"
#include "struct/indexed.h"

#define STDID_LEN 5
#define NAME_LEN 50

int main() 
{	
	clock_t t1, t2;
	
	std::cout << "\nLinear Search Program" << std::endl;
	
	t1 = clock();
	Berkley myDB("../data/A4Database.db");
	
	// Load the contents of the text file into the database
	uint64_t numberofvalues = Linear::loader(&myDB,"../data/a4data.txt");
	
	t2 = clock();
	std::cout << "Proccessed " << numberofvalues << " entries in " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds." << std::endl;
	
	/*  Loop Vairables  */
	Songs SongA;
	Songs SongB;
	song * SongAStruct;
	song * SongBStruct;
	uint32_t quriedID;
	char id[33];
	double result;
	std::string songData;
	
	
	std::ifstream file("../data/queries.txt");
	std::ofstream output("../data/linearanswers.txt");
	std::string line;
	
	t1 = clock();
	
	while(getline(file, line) && output.is_open() && output.good())
	{
		// printf("\nEnter ID for A(0 to exit): "); 
		// sfRet = scanf("%s",id);
		// 
		// if (id[0]=='0' && sfRet)
		// 	break;
		// 
		// quriedID = atoi(id);
		
		std::istringstream s(line);
		
		s >> quriedID;
		
		sprintf(id, "%d", quriedID);
		
		if(myDB.get(id))
		{
			// std::cout << "Found: " << myDB.getData() << std::endl;
			
			songData = myDB.getData();
			
			SongA.setData(&songData);
			SongAStruct = SongA.toStruct();
		}
		else
		{
			// std::cout << "Not Found" << std::endl;
			continue;
		}
		
		indexed * MatchedEntries;
		MatchedEntries = new indexed[numberofvalues - 1];
		
		char searchID[33];
		uint64_t valIndex = 0;
		
		for(uint32_t i = 1; i < numberofvalues; i++)
		{
			if( i == quriedID )
				continue;
			
			sprintf(searchID, "%d", i);
			
			if(myDB.get(searchID))
			{
				//std::cout << "Found: " << myDB.getData() << std::endl;
								 	
				songData = myDB.getData();
									
				SongB.setData(&songData);
				SongBStruct = SongB.toStruct();
				
				result = Linear::compare(SongAStruct, SongBStruct);
				
				// std::cout << "STORED>" << i << " - " << result << std::endl;
				
				MatchedEntries[valIndex].index = i;
				MatchedEntries[valIndex].value = result;
				
				valIndex++;
			}
			else
			{
				// std::cout << "Not Found" << std::endl;
				continue;
			}
		}
		
		qsort(MatchedEntries, valIndex - 1, sizeof(MatchedEntries[0]), Linear::compare);
				
		// std::cout << "Q:" << quriedID << std::endl;
				
		for(uint in = 0; in < 3; in++)
		{
			output << MatchedEntries[in].index;
			
			if(in != 2)
				output << ",";
			// std::cout << in << " - " << MatchedEntries[in].index << " - " << (double)MatchedEntries[in].value << std::endl;
		}
		
		output << "\n";
		
		delete [] MatchedEntries;
	}
	
	t2 = clock();
	std::cout << "Queries finished in " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds." << std::endl;
	
	file.close();
	
	
	return 0;
} 
 