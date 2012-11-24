#ifndef _BERKLEY_CPP_
#define _BERKLEY_CPP_

#include <db.h>
#include "Berkley.h"

DB_ENV *Berkley::env;

Berkley::Berkley(std::string dbName)
{
	//dataFile = new std::string(dbName, 0, sizeof(dbName));
	
	dataFile = dbName;
	
	// creates the database object
	ret = db_create(&db, env, 0);
	if (ret != 0) 
	{
		fprintf(stderr, "db_create: %s\n", db_strerror(ret));
	}

	// If database doesn't exist, create it 
	ret = db->open(db, NULL, dbName.c_str(), NULL, DB_HASH, DB_CREATE, 0664); 
	
	// std::cout << "Created DB: " << dataFile << std::endl;
}
Berkley::~Berkley()
{
	ret = db->close(db, 0);
	if (ret!=0) 
		db->err(db, ret, "DB->close");
	
	// if (env != NULL) {
	//     env->close(env, 0);
	// }
	
	remove(dataFile.c_str());
	
	// Delete cache files
	remove("../scratch/__db.001");
	remove("../scratch/__db.002");
	remove("../scratch/__db.003");
	
	// std::cout << "Deleted DB: " << dataFile << std::endl;
}

bool Berkley::put(char *myKey, char *myData)
{
		
	flush();
		
	key.data = myKey; 
	key.size = (1+strlen(myKey))*sizeof(char);
		
	data.data = myData;
	data.size = (1+strlen(myData))*sizeof(char);

	ret = db->put(db, NULL, &key, &data, 0); 
	if (ret!=0) 
	{
		db->err(db, ret, "DB->put");
		return 0;
	}
	else
	{
		//printf("Successfully added (%s,%s).\n",myKey,myData);
		return 1;
	}
}

bool Berkley::get(char *searchKey)
{
	flush();
	// Search to find the student with this ID			 
	key.data = searchKey; 
	key.size = (1+strlen(searchKey))*sizeof(char); 

	ret = db->get(db, NULL, &key, &data, 0);
	if (ret == 0)// Id found
	{
		#ifdef DEBUG
			#if DEBUG
				printf("Found (%s,%s).\n",searchKey,(char *)data.data);
			#endif
		#endif
		return 1;
	}
	else // Id not found 
	{
		#ifdef DEBUG
			#if DEBUG
				printf("\n%s not found\n", searchKey);
			#endif
		#endif
		return 0;
	}
}

std::string Berkley::getData()
{
	char * charData = (char *) data.data;
		
	std::string s(charData, strlen(charData));
		
	// std::cout << "DATA>" << charData << std::endl;
	// std::cout << "SIZE>" << strlen(charData) << std::endl;
	// std::cout << "STRING>" << s << std::endl;
		
	return s;
}
void Berkley::flush()
{
	memset(&key, 0, sizeof(key)); 
	memset(&data, 0, sizeof(data));
	ret = 0;
}
void Berkley::flush(char *myKey)
{
	memset(&key, 0, sizeof(*myKey)); 
	memset(&data, 0, sizeof(data));
	ret = 0;
}
void Berkley::flush(char *myKey, char *myData)
{
	memset(&key, 0, sizeof(*myKey)); 
	memset(&data, 0, sizeof(*myData));
	ret = 0;
}

#endif
