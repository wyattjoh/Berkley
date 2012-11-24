# Name: Wyatt Johnson
# Unix: wyatt
# Date: Nov 23, 2012

CC=g++ -Wall -O3
FLAGS=-lm
DBLIBS=-L/usr/local/BerkeleyDB.5.3/lib -I /usr/local/BerkeleyDB.5.3/include/ -I /usr/include -L /usr/lib
BUILD_DIR=../build
CLASS_DIR=$(BUILD_DIR)/class
SCRATCH_DIR=../scratch

all: prepare | $(CLASS_DIR) $(SCRATCH_DIR) ../build/linearsearch.o ../build/indexedsearch.o

$(CLASS_DIR):
	mkdir -p $(CLASS_DIR)/

$(SCRATCH_DIR):
	mkdir -p $(SCRATCH_DIR)/

../build/linearsearch.o: $(CLASS_DIR)/Linear.o $(CLASS_DIR)/Berkley.o $(CLASS_DIR)/Songs.o linearsearch.cpp
	$(CC) $(DBLIBS) $(FLAGS) linearsearch.cpp $(CLASS_DIR)/Linear.o $(CLASS_DIR)/Berkley.o $(CLASS_DIR)/Songs.o -o ../build/linearsearch.o -ldb

../build/indexedsearch.o: $(CLASS_DIR)/Linear.o $(CLASS_DIR)/Index.o $(CLASS_DIR)/Berkley.o $(CLASS_DIR)/Songs.o linearsearch.cpp
	$(CC) $(DBLIBS) $(FLAGS) indexedsearch.cpp $(CLASS_DIR)/Linear.o $(CLASS_DIR)/Index.o $(CLASS_DIR)/Berkley.o $(CLASS_DIR)/Songs.o -o ../build/indexedsearch.o -ldb

$(CLASS_DIR)/Berkley.o: class/Berkley.cpp
	$(CC) $(DBLIBS) -c class/Berkley.cpp -o $(CLASS_DIR)/Berkley.o

$(CLASS_DIR)/Linear.o: class/Linear.cpp
	$(CC) $(DBLIBS) -c class/Linear.cpp -o $(CLASS_DIR)/Linear.o

$(CLASS_DIR)/Index.o: class/Index.cpp
	$(CC) $(DBLIBS) -c class/Index.cpp -o $(CLASS_DIR)/Index.o

$(CLASS_DIR)/Songs.o: class/Songs.cpp
	$(CC) $(DBLIBS) -c class/Songs.cpp -o $(CLASS_DIR)/Songs.o

clean:
	rm -f ../build/*.o $(CLASS_DIR)/*.o ../data/*.db ../scratch/*
	
prepare:
	rm -f ../data/*.db ../scratch/*