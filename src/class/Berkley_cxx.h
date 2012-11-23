#ifndef _BERKLEY_CXX_H_
#define _BERKLEY_CXX_H_

#include <db_cxx.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#define DATABASE "../data/A4Database.db"

// class Berkley {
// public:
// 	
// 	Berkley(std::string dbName);
// 	~Berkley();
// 	
// 	bool put(char *myKey, char *myData);
// 	
// 	bool get(char *searchKey);
// 	
// 	std::string getData();
// private:
// 	void flush();
// 	void flush(char *myKey);
// 	void flush(char *myKey, char *myData);
// 	
// 	DB *db;
// 	DBT key, data;
// 	int ret;
// 	std::string dataFile;
// };

class Berkley_cxx {
public:
	Berkley_cxx(const char * dbName);
	~Berkley_cxx();
	
	std::string * cursorGet(int * searchKey);
	void cursorPut(std::ifstream * file);
	void put(int * index, std::string * dataString);
	
	Db * getDB();
	Dbc * getCursor();
	
	// 
	// bool put(int *myKey, std::string *myData);
	// 
	// bool get(int *searchKey);
	// 
	// std::string getData();
	
private:
	// void flush();
	
	// DB Open
	Db *db;
	static const uint32_t oFlags = DB_CREATE;
	
	// DB Cursor
	Dbc *cursorp;
	
	std::string *dbFile;
	
	// std::string dataFile;
};

#endif
