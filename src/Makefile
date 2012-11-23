CC=g++ -Wall -O3
FLAGS=-lm
DBLIBS=-L/usr/local/BerkeleyDB.5.3/lib -I /usr/local/BerkeleyDB.5.3/include/ -I /usr/include -L /usr/lib
BUILD_DIR=../build
CLASS_DIR=$(BUILD_DIR)/class

all: | $(CLASS_DIR) ../build/linearsearch.o

$(CLASS_DIR):
	mkdir -p $(CLASS_DIR)/

../build/linearsearch.o: $(CLASS_DIR)/Linear.o $(CLASS_DIR)/Berkley_cxx.o $(CLASS_DIR)/Songs.o linearsearch.cpp
	$(CC) $(DBLIBS) $(FLAGS) linearsearch.cpp $(CLASS_DIR)/Linear.o $(CLASS_DIR)/Berkley_cxx.o $(CLASS_DIR)/Songs.o -o ../build/linearsearch.o -ldb_cxx

$(CLASS_DIR)/Berkley.o: class/Berkley.cpp
	$(CC) $(DBLIBS) -c class/Berkley.cpp -o $(CLASS_DIR)/Berkley.o

$(CLASS_DIR)/Berkley_cxx.o: class/Berkley_cxx.cpp
	$(CC) $(DBLIBS) -c class/Berkley_cxx.cpp -o $(CLASS_DIR)/Berkley_cxx.o

$(CLASS_DIR)/Linear.o: class/Linear.cpp
	$(CC) $(DBLIBS) -c class/Linear.cpp -o $(CLASS_DIR)/Linear.o

$(CLASS_DIR)/Songs.o: class/Songs.cpp
	$(CC) -c class/Songs.cpp -o $(CLASS_DIR)/Songs.o

clean:
	rm -f ../build/*.o $(CLASS_DIR)/*.o ../data/*.db 