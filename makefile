CC = g++
COPTS = -c -g -O3 -DDEBUG -W -Wall -Werror -pedantic
OBJS = array.o personne.o tools.o main.o jstr.o jfile.o
TARGET = personne

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

array.o : array.cc array.h
	$(CC) $(COPTS) array.cc

jstr.o : jstr.cc jstr.h tools.h
	$(CC) $(COPTS) jstr.cc

jfile.o : jfile.cc jfile.h jstr.h tools.h
	$(CC) $(COPTS) jfile.cc

tools.o : tools.cc tools.h
	$(CC) $(COPTS) tools.cc

personne.o : personne.cc personne.h tools.h
	$(CC) $(COPTS) personne.cc

main.o : main.cc tools.h array.h personne.h
	$(CC) $(COPTS) main.cc

clean :
	rm -f *~ *.o $(OBJS) $(TARGET) *.stackdump \#*\#

