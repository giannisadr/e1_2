

all: fconc

fconc: fconc.o
	gcc fconc.o -o fconc

fconc.o: fconc.c
	gcc -Wall -c fconc.c

clean:
	rm -f *.o fconc.out

