IPATH=   -I.
CFLAGS=  -Wall -O3 ${IPATH} -DPBLTEST
LDFLAGS= -lpthread
CC= gcc

THELIB    = queue/src/libpbl.a

EXE_OBJS1 = main.o
THEEXE1   = t

CLEAR = tests/fills/clean.sh
CHARGE = tests/fills/chrg.sh
THDS = tests/fills/ThreadsTest.sh
REGULAR = tests/fills/RegularTest.sh

all: $(THEEXE1)

$(THEEXE1):  $(EXE_OBJS1)
	$(CC) -O2 -o $(THEEXE1) $(EXE_OBJS1) $(THELIB) $(LDFLAGS) 

clean:
	rm -rf *.o $(THEEXE1)

test: $(THEEXE1)
	./$(CLEAR)
	./$(CHARGE)
	./$(THDS)	
	./$(REGULAR)
	echo
