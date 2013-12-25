CC= g++ -o

CCL= g++ -c

PREFIX = /opt/gnome

CFLAGS = `pkg-config --cflags libgnomeui-2.0` -ansi -Wall \
			-DPREFIX=\""$(PREFIX)"\" \
			-DDATADIR=\""$(PREFIX)/share"\" \
			-DSYSCONFDIR=\""$(PREFIX)/etc"\" \
			-DLIBDIR=\""$(PREFIX)/lib"\"
			
LIBS = `pkg-config --libs libgnomeui-2.0`

automatown: main.cpp Stats.o Square.o XmlModule.o
	$(CC) automatown main.cpp Stats.o Square.o XmlModule.o `xml2-config --libs` $(CFLAGS) $(LIBS)

Neighbor.o: Neighbor.cpp Neighbor.h
	$(CCL) Neighbor.cpp

Stats.o: Stats.cpp Stats.h Square.o
	$(CCL) Stats.cpp Square.o

Square.o: Square.cpp Square.h Structure.h
	$(CCL) Square.cpp
	
XmlModule.o: XmlModule.cpp XmlModule.h Structure.h
	$(CCL) `xml2-config --cflags` XmlModule.cpp $(CFLAGS) $(LIBS)
	
clean:
	/bin/rm -f *~ *.o automatown
