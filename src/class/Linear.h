#ifndef _LINEAR_H_
#define _LINEAR_H_

#include "../struct/song.h"
// #include "Berkley.h"
#include "Berkley_cxx.h"

class Linear
{
public:
	Linear();
	static double compare(song *SongA, song *SongB);
	static int compare(const void * a, const void * b);
	static uint32_t loader(Berkley_cxx *myDB, const char * filename);
	static void query(Berkley_cxx *myDB, int index);
};

#endif
