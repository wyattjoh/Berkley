// Name: Wyatt Johnson
// Unix: wyatt
// Date: Nov 23, 2012

#ifndef _INDEX_CPP_
#define _INDEX_CPP_

// My Header
#include "Index.h"

// Standard Libs
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <math.h>

// Include Classes
#include "Berkley.h"
#include "Songs.h"

// Include Structs
#include "../struct/song.h"
#include "../struct/indexed.h"

Index::Index()
{
	
}

double Index::compare(song *SongA, song *SongB)
{
	double result = 42;
	
	int matchingEntries = 0;
	
	int * A;
	int * B;
	
	if(SongA->rCount >= SongB->rCount)
	{
		A = new int[SongA->rCount];
		B = new int[SongA->rCount];
	}
	else
	{
		A = new int[SongB->rCount];
		B = new int[SongA->rCount];
	}
	
	for(int i = 0; i< SongA->rCount; i++)
	{
		for(int f = 0; f<SongB->rCount; f++)
		{
			
			if(SongA->ratings[i].User.compare(SongB->ratings[f].User) == 0)
			{
				A[matchingEntries] = SongA->ratings[i].rating;
				B[matchingEntries] = SongB->ratings[f].rating;
				
				matchingEntries++;
			}
		}
	}
	
	if( matchingEntries > 0 )
	{
		uint64_t sum = 0;
		
		for(int i = 0; i < matchingEntries; i++)
		{
			uint64_t temp = (A[i] - B[i]);
			sum += temp*temp;
		}
		
		result = sqrt(sum);
		
		result /= matchingEntries;
	}
	
	delete [] A;
	delete [] B;
	
	return result;
}

int Index::compare(const void * b, const void * a)
{
	indexed *struct_a = (indexed *) a;
	indexed *struct_b = (indexed *) b;
	
	if(struct_a->value < struct_b->value)
		return 1;
	else if(struct_a->value == struct_b->value)
		return 0;
	else
		return -1;
}

uint32_t Index::loader(Berkley *ourDB, const char * filename)
{
	std::ifstream file(filename);
	
	std::string line;
	
	int count = 0;
		
	while(getline(file, line))
	{
		// std::cout << "Line(" << line << ")" << std::endl;
		
		Songs record = Songs();
		record.setData(&line);
		record.updateUsersDB(ourDB);
		
		// song *rSong = record.toStruct();
		// 	
		// // std::cout << "DATA ===> ID>" << rSong->id << std::endl;
		// // std::cout << "DATA ===> TITLE>" << rSong->Title << std::endl;
		// // std::cout << "DATA ===> ARTSITS>" << rSong->Artists << std::endl;
		// 	
		// char index[33];
		// 
		// sprintf(index, "%d", rSong->id);
		// 
		// // int charSize = (*record).charSize();
		// 
		// std::string songString = record.toString();
		// 
		// // std::cout << "String size: " << songString.size() << std::endl;
		// 
		// // char * s = new char[charSize + 1];
		// // char * s = new char[songString.size()];
		// 
		// // std::copy(songString.begin(), songString.end(), s);
		// 
		// char *s = (char*)songString.c_str();
		// 	
		// // std::cout << index << " <==> " << s << std::endl;
		// 
		// // std::cout << "<><>" << std::endl;
		// 
		// ourDB->put(index, s);
			
		count++;
		
		// delete s;
		// delete record;
	}
		
	file.close();
		
	return count;
}

#endif
