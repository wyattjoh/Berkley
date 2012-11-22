#ifndef _BERKLEY_H_
#define _BERKLEY_H_

#include <db.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define DATABASE "../data/A4Database.db"

class Berkley {
public:
	static bool put(char *myKey, char *myData);
	static bool get(char *searchKey);
	static std::string getData();
	Berkley();
	~Berkley();
private:
	static void flush();
	static void flush(char *myKey, char *myData);
	static DB *db;
	static DBT key, data;
	static int ret;
};

#endif
