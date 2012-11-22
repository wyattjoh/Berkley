#ifndef _SONG_H_
#define _SONG_H_

#include <string.h>

struct rating {
	std::string User;
	uint8_t rating;
};

struct song {
	int id;
	std::string Title;
	std::string Artists;
	rating ratings[255];
	std::string rat[255];
};

#endif
