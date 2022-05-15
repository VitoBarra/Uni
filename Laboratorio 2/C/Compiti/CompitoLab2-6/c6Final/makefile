
CC=gcc
CFLAGS=-g -Wall -I. 
LDLIBS= -pthread

# eseguibile da compilare
MAIN=mergeMT

all: $(MAIN)

$(MAIN): $(MAIN).o unboundedqueue.o

# target che cancella eseguibili e file oggetto
clean:
	rm -f $(MAIN) *.o  

# target che esegue test 1
test1: $(MAIN)
	./$(MAIN) 3 10 test1
	echo checksum corretto: 117615

# target che esegue test 2
test2: $(MAIN)
	./$(MAIN) 5 10 test2
	echo checksum corretto: 714227

# target che esegue test 3
test3: $(MAIN)
	./$(MAIN) 2 1000 test3
	echo checksum corretto: 1632655278

# target che esegue test 4
test4: $(MAIN)
	./$(MAIN) 3 1000 test4
	echo checksum corretto: 0

compito: ../c6Final/
	tar -czvf ../$@.tar.gz $^