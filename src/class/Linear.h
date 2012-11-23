#ifndef _LINEAR_H_
#define _LINEAR_H_

#include "../struct/song.h"

class Linear
{
public:
	Linear();
	static double compare(song *SongA, song *SongB);
	static int compare(const void * a, const void * b);
private:
};

// class sortIndicies
// {
// private:
// 	int * mparr;
// public:
// 	sortIndicies(int* parr) : mparr(parr) {}
// 	bool operator()(int i, int j) {return mparr[i] < mparr[j]}
// };

#endif
