#ifndef _BERKLEY_CPP_
#define _BERKLEY_CPP_

#include <db_cxx.h>
#include "Berkley_cxx.h"

Berkley_cxx::Berkley_cxx(const char* dbName)
{
	maxLength = 0;
	dbFile = new std::string(dbName);
	
	// std::cout << "Created " << *dbFile << std::endl;
	
	db = new Db(NULL, 0); 
	
	try {
	    // Open the database
	    db->open(NULL,                // Transaction pointer 
	            dbName,          // Database file name 
	            NULL,                // Optional logical database name
	            DB_BTREE,            // Database access method
	            oFlags,              // Open flags
	            0);                  // File mode (using defaults)
	// DbException is not subclassed from std::exception, so
	// need to catch both of these.
	} catch(DbException &e) {
	    // Error handling code goes here    
	} catch(std::exception &e) {
	    // Error handling code goes here
	} 
}

Berkley_cxx::~Berkley_cxx()
{
	try {
	    // Close the database
	    db->close(0);
	// DbException is not subclassed from std::exception, so
	// need to catch both of these.
	} catch(DbException &e) {
	    // Error handling code goes here    
	} catch(std::exception &e) {
	    // Error handling code goes here
	}
	
	// if (cursorp != NULL)
	//     cursorp->close();
	
	remove(dbFile->c_str());
	
	// std::cout << "Removed " << *dbFile << std::endl;
	
	delete dbFile;
	delete db;
}

Db * Berkley_cxx::getDB()
{
	return db;
}

Dbc * Berkley_cxx::getCursor()
{
	return cursorp;
}

std::string Berkley_cxx::cursorGet(int * searchKey)
{
	try {
	    // database open omitted for clarity

	    // Get a cursor
	    db->cursor(NULL, &cursorp, 0);

	    // Search criteria
	    // char *search_key = "Alaska";
	    // char *search_data = "Fa";

	    // Set up our DBTs
	    Dbt key(searchKey, sizeof(int));
		Dbt data;
		
	    // Position the cursor to the first record in the database whose
	    // key matches the search key and whose data begins with the search
	    // data.
	    int ret = cursorp->get(&key, &data, DB_SET);
		
		if (!ret) {
	        // Do something with the data
			
			std::string MyData = *((std::string *) data.get_data());
			
			std::cout << "DBGET>" << (std::string *) data.get_data()  <<  " <<IS>> " << MyData << std::endl;
			
			if (cursorp != NULL)
			    cursorp->close();
			
			// return (void *)data.get_data();
			return MyData;
	    }
		
		if (cursorp != NULL)
		    cursorp->close();
		
		return NULL;
		
	} catch(DbException &e) {
	        db->err(e.get_errno(), "Error!");
	} catch(std::exception &e) {
	        db->errx("Error! %s", e.what());
	}
	
	return NULL;
}

// void Berkley_cxx::cursorPut(int * index, std::string dataString)
void Berkley_cxx::cursorPut(std::ifstream * file)
{
	
}

void Berkley_cxx::put(int * index, const char * dataString)//std::string * dataString)
{
	// char *description = "Grocery bill.";
	// float money = 122.45;
	
	// std::string myDataString = * dataString;
	int myIndex = *index;

	Dbt key(&myIndex, sizeof(int));
	// Dbt data(&myDataString, myDataString.capacity());
	Dbt data(&dataString, strlen(dataString));
	
	if(maxLength < strlen(dataString))
		maxLength = strlen(dataString);
	
	std::cout << "INSERT>" << myIndex << "," << dataString << std::endl;
	
	int ret = db->put(NULL, &key, &data, DB_NOOVERWRITE);
	if (ret == DB_KEYEXIST) {
	    db->err(ret, "Put failed because key %f already exists", index);
	}
	else
	{
		// get(index);
	}
}

void Berkley_cxx::put(int * index, std::string * dataString)
{
	// char *description = "Grocery bill.";
	// float money = 122.45;
	
	std::string myDataString = * dataString;
	int myIndex = *index;

	Dbt key(&myIndex, sizeof(int));
	Dbt data(&myDataString, myDataString.capacity());
	
	// if(maxLength < strlen(dataString))
	// 	maxLength = strlen(dataString);
	
	std::cout << "INSERT>" << myIndex << "," << myDataString << std::endl;
	
	int ret = db->put(NULL, &key, &data, DB_NOOVERWRITE);
	if (ret == DB_KEYEXIST) {
	    db->err(ret, "Put failed because key %f already exists", index);
	}
	else
	{
		// std::string *myVerify = getP(index);
		// std::cout << "VERIFY>" << *myVerify << std::endl;
	}
}

std::string Berkley_cxx::get(int * index)
{
	// std::string MyData = "ge";
	
	try {
		Dbt key, data;
		
		// char *dataBuffer;
		
		// std::string *myData;

		key.set_data(index);
		key.set_size(sizeof(int));
	
		// data.set_data(myData);
		// data.set_ulen(maxLength);
		// data.set_flags(DB_DBT_USERMEM);
		
		// std::cout << "Getting: " << *index << std::endl;
		
		db->get(NULL, &key, &data, 0);
		
		// std::cout << *((std::string*) data.get_data()) << std::endl;
		
		// std::cout << "Got it: " << (char *) data.get_data() << std::endl;
		
		// std::string MyData = "ge";
		// std::string MyData = *((std::string*) data.get_data());
		std::string MyData = std::string((const char *) data.get_data());
		
		// std::cout << "Got it: " << MyData << std::endl;
		
		return MyData;
		
		// std::cout << "DATA>" << *index << "," << MyData << std::endl;
	
	} catch(DbException &e) {
	        db->err(e.get_errno(), "Error!");
			std::cout << "exception detected" << std::endl;
			return NULL;
	} catch(std::exception &e) {
	        db->errx("Error! %s", e.what());
			std::cout << "exception detected" << std::endl;
			return NULL;
	}
	
	std::cout << "Ok?" << std::endl;
	
	return NULL;
}

std::string * Berkley_cxx::getP(int * index)
{
	// std::string MyData = "ge";
	
	try {
		Dbt key, data;
		
		// char *dataBuffer;
		
		// std::string *myData;

		key.set_data(index);
		key.set_size(sizeof(int));
	
		// data.set_data(myData);
		// data.set_ulen(maxLength);
		// data.set_flags(DB_DBT_USERMEM);
		
		// std::cout << "Getting: " << *index << std::endl;
		
		db->get(NULL, &key, &data, 0);
		
		// std::cout << *((std::string*) data.get_data()) << std::endl;
		
		// std::cout << "Got it: " << (char *) data.get_data() << std::endl;
		
		// std::string MyData = "ge";
		std::string *MyData = (std::string *) data.get_data();
		// std::string MyData = std::string((const char *) data.get_data());
		
		// std::cout << "Got it: " << *MyData << std::endl;
		
		return (std::string *) data.get_data();
		
		// std::cout << "DATA>" << *index << "," << MyData << std::endl;
	
	} catch(DbException &e) {
	        db->err(e.get_errno(), "Error!");
			std::cout << "exception detected" << std::endl;
			return NULL;
	} catch(std::exception &e) {
	        db->errx("Error! %s", e.what());
			std::cout << "exception detected" << std::endl;
			return NULL;
	}
	
	std::cout << "Ok?" << std::endl;
	
	return NULL;
}

// Berkley::Berkley(std::string dbName)
// {
// 	//dataFile = new std::string(dbName, 0, sizeof(dbName));
// 	
// 	dataFile = dbName;
// 	
// 	std::cout << "Created DB: " << dataFile << std::endl;
// 	
// 	// creates the database object
// 	ret = db_create(&db, NULL, 0);
// 	if (ret != 0) 
// 	{
// 		fprintf(stderr, "db_create: %s\n", db_strerror(ret));
// 	}
// 
// 	// opens database
// 	// ret = db->open(db, NULL, dbName, NULL, DB_HASH, 0, 0664);
// 	// if (ret != 0)
// 	// {
// 		// If database doesn't exist, create it 
// 		ret = db->open(db, NULL, dbName.c_str(), NULL, DB_HASH, DB_CREATE, 0664); 
// 	// }
// }
// Berkley::~Berkley()
// {
// 	ret = db->close(db, 0);
// 	if (ret!=0) 
// 		db->err(db, ret, "DB->close");
// 	
// 	remove(dataFile.c_str());
// 	
// 	std::cout << "Deleted DB: " << dataFile << std::endl;
// }
// 
// bool Berkley::put(char *myKey, char *myData)
// {
// 		
// 	flush(myKey, myData);
// 		
// 	key.data = myKey; 
// 	key.size = (1+strlen(myKey))*sizeof(char);
// 		
// 	data.data = myData;
// 	data.size = (1+strlen(myData))*sizeof(char);
// 
// 	ret = db->put(db, NULL, &key, &data, 0); 
// 	if (ret!=0) 
// 	{
// 		db->err(db, ret, "DB->put");
// 		return 0;
// 	}
// 	else
// 	{
// 		//printf("Successfully added (%s,%s).\n",myKey,myData);
// 		return 1;
// 	}
// }
// 
// bool Berkley::get(char *searchKey)
// {
// 	flush(searchKey);
// 	// Search to find the student with this ID			 
// 	key.data = searchKey; 
// 	key.size = (1+strlen(searchKey))*sizeof(char); 
// 
// 	ret = db->get(db, NULL, &key, &data, 0);
// 	if (ret == 0)// Id found
// 	{
// 		#ifdef DEBUG
// 			#if DEBUG
// 				printf("Found (%s,%s).\n",searchKey,(char *)data.data);
// 			#endif
// 		#endif
// 		return 1;
// 	}
// 	else // Id not found 
// 	{
// 		#ifdef DEBUG
// 			#if DEBUG
// 				printf("\n%s not found\n", searchKey);
// 			#endif
// 		#endif
// 		return 0;
// 	}
// }
// 
// std::string Berkley::getData()
// {
// 	char * charData = (char *) data.data;
// 		
// 	std::string s(charData, strlen(charData));
// 		
// 	// std::cout << "DATA>" << charData << std::endl;
// 	// std::cout << "SIZE>" << strlen(charData) << std::endl;
// 	// std::cout << "STRING>" << s << std::endl;
// 		
// 	return s;
// }
// void Berkley::flush()
// {
// 	memset(&key, 0, sizeof(key)); 
// 	memset(&data, 0, sizeof(data));
// 	ret = 0;
// }
// void Berkley::flush(char *myKey)
// {
// 	memset(&key, 0, sizeof(*myKey)); 
// 	memset(&data, 0, sizeof(data));
// 	ret = 0;
// }
// void Berkley::flush(char *myKey, char *myData)
// {
// 	memset(&key, 0, sizeof(*myKey)); 
// 	memset(&data, 0, sizeof(*myData));
// 	ret = 0;
// }
// 
#endif
