CC= g++ `pkg-config --cflags --libs gtkmm-2.4`
CCL= g++

automatown: main.cpp Square.o
	$(CC) -o automatown main.cpp

Square.o: Square.cpp Square.h Structure.h
	$(CCL) -c Square.cpp
	
clean:
	/bin/rm -f *~ *.o automatown
