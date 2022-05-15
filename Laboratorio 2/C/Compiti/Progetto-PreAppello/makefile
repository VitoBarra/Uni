
CC=gcc
CFLAGS=-g -Wall -I.
LDLIBS= -pthread

# eseguibile da compilare
MAIN=farm

.PHONY: test clean

all: $(MAIN)


 $(MAIN):  boundedqueue
	$(CC) $@.c $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ boundedqueue.o   $(LDLIBS)


boundedqueue:
	$(CC) $@.c -c $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@.o   $(LDLIBS)


generafile: 
	$(CC) $@.c $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@
	chmod +x ./generafile

# target che cancella eseguibili e file oggetto
clean:
	rm -f $(MAIN) *.o

testRNG: all generafile
	./generafile RNGfile 100 
	./$(MAIN) ./RNGfile

test: all
	./test.sh



compito: ../Progetto-PreAppello/
	tar -czvf ../$@.tar.gz $^