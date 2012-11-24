#ifndef _BERKLEY_H_
#define _BERKLEY_H_

#include <db.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//#define DATABASE "../data/A4Database.db"

class Berkley {
public:
	bool put(char *myKey, char *myData);
	bool get(char *searchKey);
	std::string getData();
	Berkley(std::string dbName);
	~Berkley();
	
	static void iniEnv()
	{
		env = NULL;
		
		if( db_env_create(&env, 0) )
		{
			std::cout << "Cannot create env" << std::endl;
			return;
		}
		
		if( env->set_data_dir(env, "../scratch/") != 0 )
		{
			std::cout << "Cannot set data directory (../scratch/)." << std::endl;
			return;
		}
		
		/* Open an environment with just a memory pool. */
		if( env->open(env, "../scratch/", DB_CREATE | DB_INIT_MPOOL, 0) != 0 )
		{
			std::cout << "Cannot open env." << std::endl;
			return;
		}
		
	}
private:
	static int dbCount;
	static DB_ENV *env;
	
	void flush();
	void flush(char *myKey);
	void flush(char *myKey, char *myData);
	DB *db;
	DBT key, data;
	int ret;
	std::string dataFile;
};

#endif
