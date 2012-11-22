CC=g++ -Wall -O3
FLAGS=-ldb_cxx -lm
DBLIBS=-L/usr/local/BerkeleyDB.5.3/lib -I /usr/local/BerkeleyDB.5.3/include/ 
BUILD_DIR=../build
CLASS_DIR=$(BUILD_DIR)/class

all: | $(CLASS_DIR) ../build/app.o

$(CLASS_DIR):
	mkdir -p $(CLASS_DIR)/

../build/app.o: $(CLASS_DIR)/Berkley.o $(CLASS_DIR)/Songs.o app.cpp
	$(CC) $(FLAGS) $(DBLIBS) app.cpp $(CLASS_DIR)/Berkley.o $(CLASS_DIR)/Songs.o -o ../build/app.o

$(CLASS_DIR)/Berkley.o: class/Berkley.cpp
	$(CC) $(DBLIBS) -c class/Berkley.cpp -o $(CLASS_DIR)/Berkley.o

$(CLASS_DIR)/Songs.o: class/Songs.cpp
	$(CC) -c class/Songs.cpp -o $(CLASS_DIR)/Songs.o

sync: 
	rsync -avz . ugl:~/berkley/

mac: clean sync remote-build
	
linux: ../build/app.o
	
remote-build:
	ssh ugl 'cd ~/berkley/; make linux;valgrind --tool=memcheck ./../build/app.o 1> /dev/null;'

clean:
	rm -f ../build/*.o $(CLASS_DIR)/*.o ../data/*.db 