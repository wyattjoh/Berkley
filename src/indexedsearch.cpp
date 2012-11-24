// Berkeley DB Example
// This program creates/uses a hash file to hold (id/student_name) of students 
// gcc -lm -ldb -I /usr/local/include -L /usr/local/lib -O bdb_sample.c

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <time.h>
#include <list>

// Include Classes
#include "class/Berkley.h"
#include "class/Songs.h"
#include "class/Index.h"
#include "class/Linear.h"

// Include Structs
#include "struct/song.h"
#include "struct/indexed.h"

#define STDID_LEN 5
#define NAME_LEN 50

int main() 
{	
	clock_t t1, t2;
	
	std::cout << "\nIndexed Search Program" << std::endl;
	
	DB_ENV * dbEnv = Berkley::iniEnv();
	
	Index objectIndex;
	Index objectIndex2;
	
	t1 = clock();
	
	Berkley* myDB = new Berkley("../data/A4Database.db");
	
	// Load the contents of the text file into the database
	uint64_t numberofvalues = Linear::loader(myDB,"../data/a4data.txt");
	
	t2 = clock();
	
	std::cout << "Linear Database Proccessed " << numberofvalues << " entries in " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds." << std::endl;
	
	t1 = clock();
	
	Berkley* indexDB = new Berkley("../data/A4IndexDatabase.db");
	
	numberofvalues = objectIndex2.loader(indexDB,"../data/a4data.txt");
	
	t2 = clock();
	
	std::cout << "Indexed Database Proccessed " << numberofvalues << " entries in " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds." << std::endl;
	
	// std::cout << std::string::npos << std::endl;
	
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
	std::ofstream output("../data/indexedanswers.txt");
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
			
		if(myDB->get(id))
		{
			// std::cout << "Found: " << myDB->getData() << std::endl;
				
			songData = myDB->getData();
				
			SongA.setData(&songData);
			SongAStruct = SongA.toStruct();
		}
		else
		{
			// std::cout << "Not Found" << std::endl;
			continue;
		}
		
		std::string movData;
		// Check across SongAStruct.ratings[i].Title to compile
		for(int rIndex = 0; rIndex < SongAStruct->rCount; rIndex++)
		{
			char * userChar = (char*)SongAStruct->ratings[rIndex].User.c_str();
			
			if(indexDB->get(userChar))
			{
				movData += indexDB->getData();
				
			}
			else
			{
				std::cout << "But... this can't happen." << std::endl;
				
				break;
			}
		}
		
		std::list<int> songList;
		
		int cPos;
		
		while(movData.length() > 0)
		{
			int tmp;
			
			cPos = movData.find(",");
			std::string substring = movData.substr(0, cPos);
			
			// std::cout << substring << std::endl;
			
			std::istringstream s(substring);
			
			s >> tmp;
			
			songList.push_back(tmp);
			
			// std::cout << tmp << std::endl;
			
			movData.erase(0, cPos + 1);
		}
		
		// Process list...
		
		songList.remove(quriedID);
		
		songList.sort();
		
		songList.unique();
		
		int valIndex = 0;
		char searchID[33];
		indexed * MatchedEntries;
		MatchedEntries = new indexed[songList.size()];
		
		for (std::list<int>::iterator it=songList.begin(); it!=songList.end(); ++it)
		{
			// Song ID Contained in *it;
			// std::cout << " " << *it;
			
			sprintf(searchID, "%d", *it);
			
			if(myDB->get(searchID))
			{
				//std::cout << "Found: " << myDB->getData() << std::endl;
									 	
				songData = myDB->getData();
										
				SongB.setData(&songData);
				SongBStruct = SongB.toStruct();
					
				result = Index::compare(SongAStruct, SongBStruct);
					
				// std::cout << "STORED>" << i << " - " << result << std::endl;
					
				MatchedEntries[valIndex].index = *it;
				MatchedEntries[valIndex].value = result;
				
				valIndex++;
			}
			else
			{
				// std::cout << "Not Found" << std::endl;
				continue;
			}
			
		}
		
		qsort(MatchedEntries, valIndex - 1, sizeof(MatchedEntries[0]), Index::compare);
					
		// std::cout << "Q:" << quriedID << std::endl;
					
		for(uint in = 0; in < 3; in++)
		{
			output << MatchedEntries[in].index;
				
			if(in != 2)
				output << ",";
			// std::cout << in << " - " << MatchedEntries[in].index << " - " << (double)MatchedEntries[in].value << std::endl;
		}
			
		output << "\n";
			
		delete MatchedEntries;
	}
	
	t2 = clock();
	
	std::cout << "Queries finished in " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds." << std::endl;
		
	file.close();
	
	// std::cout << "Cleaning up..." << std::endl;
	
	delete myDB;
	delete indexDB;
	
	if (dbEnv != NULL) {
	    dbEnv->close(dbEnv, 0);
	}
	
	return 0;
} 
 