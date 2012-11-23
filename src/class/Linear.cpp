#ifndef _LINEAR_CPP_
#define _LINEAR_CPP_

#include "Linear.h"
#include <string.h>
#include <math.h>
#include "../struct/indexed.h"

Linear::Linear()
{
	
}

double Linear::compare(song *SongA, song *SongB)
{
	double result = 42;
	
	int matchingEntries = 0;
	
	int * A;
	int * B;
	
	// uint64_t sum = 0;
	// 
	// for(uint64_t i = 0; )
	// 
	
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
				std::cout << "Rating " << SongA->ratings[i].User << " " << SongA->ratings[i].rating << std::endl;
				std::cout << SongA->ratings[i].User << " (" << SongA->ratings[i].rating << ")" << " vs " << SongB->ratings[f].User << " (" << SongB->ratings[f].rating << ")" << std::endl;
				
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
			
			std::cout << "Sum: " << sum << std::endl;
		}
		
		result = sqrt(sum);
		
		std::cout << "Result: " << result << std::endl;
		
		result /= matchingEntries;
		
		std::cout << "Result: " << result << std::endl;
	}
	
	delete [] A;
	delete [] B;
	
	return result;
}

int Linear::compare(const void * b, const void * a)
{
	indexed *struct_a = (indexed *) a;
	indexed *struct_b = (indexed *) b;
	
	if(struct_a->value < struct_b->value)
		return 1;
	else if(struct_a->value == struct_b->value)
		return 0;
	else
		return -1;
	
	// return (*(int*) a - *(int*) b );
}

// struct indexed
// {
// 	uint64_t index;
// 	double value;
// };


#endif
