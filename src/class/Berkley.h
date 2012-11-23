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
	bool put(char *myKey, char *myData);
	bool get(char *searchKey);
	std::string getData();
	Berkley(std::string dbName);
	~Berkley();
private:
	void flush();
	void flush(char *myKey);
	void flush(char *myKey, char *myData);
	DB *db;
	DBT key, data;
	int ret;
	std::string dataFile;
};

#endif
