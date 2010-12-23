CC= g++ -o

CCL= g++ -c

PREFIX = /opt/gnome

CFLAGS = `pkg-config --cflags libgnomeui-2.0` -ansi -Wall \
			-DPREFIX=\""$(PREFIX)"\" \
			-DDATADIR=\""$(PREFIX)/share"\" \
			-DSYSCONFDIR=\""$(PREFIX)/etc"\" \
			-DLIBDIR=\""$(PREFIX)/lib"\"
			
LIBS = `pkg-config --libs libgnomeui-2.0`

xmlt: xml_test.cpp
	$(CC) xmlt xml_test.cpp $(CFLAGS) $(LIBS)

clean:
	/bin/rm -f *~ *.o xmltest
