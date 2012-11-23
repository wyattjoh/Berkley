#ifndef _LINEAR_CPP_
#define _LINEAR_CPP_

#include "Linear.h"
#include <string.h>
#include <math.h>

Linear::Linear()
{
	
}

double Linear::compare(song *SongA, song *SongB)
{
	double result = 0;
	
	int matchingEntries = 0;
	
	int * A;
	int * B;
	
	// uint32_t sum = 0;
	// 
	// for(uint32_t i = 0; )
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
			// std::cout << "Rating " << SongA->ratings[i].User << " " << SongA->ratings[i].rating << std::endl;
			if(SongA->ratings[i].User.compare(SongB->ratings[f].User) == 0)
			{
				std::cout << SongA->ratings[i].User << " (" << SongA->ratings[i].rating << ")" << " vs " << SongB->ratings[f].User << " (" << SongB->ratings[f].rating << ")" << std::endl;
				
				A[matchingEntries] = SongA->ratings[i].rating;
				B[matchingEntries] = SongB->ratings[f].rating;
				
				matchingEntries++;
			}
		}
	}
	
	if( matchingEntries > 0 )
	{
		uint32_t sum = 0;
		
		for(int i = 0; i < matchingEntries; i++)
		{
			uint32_t temp = (A[i] - B[i]);
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



#endif
