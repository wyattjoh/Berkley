#ifndef _INDEX_H_
#define _INDEX_H_

#include "../struct/song.h"
#include "Berkley.h"

class Index
{
public:
	Index();
	static double compare(song *SongA, song *SongB);
	static int compare(const void * a, const void * b);
	static uint32_t loader(Berkley *myDB, const char * filename);
};

#endif
