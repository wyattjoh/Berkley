CC=g++ -Wall -O3
FLAGS=-ldb_cxx -lm
DBLIBS=-L/usr/local/BerkeleyDB.5.3/lib -I /usr/local/BerkeleyDB.5.3/include/ 

all: ../build/app.o

../build/app.o: ../build/class/Berkley.o ../build/class/Songs.o app.cpp
	$(CC) $(FLAGS) $(DBLIBS) app.cpp ../build/class/Berkley.o ../build/class/Songs.o -o ../build/app.o

../build/class/Berkley.o: class/Berkley.cpp
	$(CC) $(DBLIBS) -c class/Berkley.cpp -o ../build/class/Berkley.o

../build/class/Songs.o: class/Songs.cpp
	$(CC) -c class/Songs.cpp -o ../build/class/Songs.o

sync: 
	rsync -avz . ugl:~/berkley/

mac: clean sync remote-build
	
linux: ../build/app.o
	
remote-build:
	ssh ugl 'cd ~/berkley/; make linux;valgrind --tool=memcheck ./../build/app.o 1> /dev/null;'

clean:
	rm -f ../build/*.o ../build/class/*.o ../data/*.db 