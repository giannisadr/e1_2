

all: clean fconc

fconc: fconc.o
	gcc fconc.o -o fconc

fconc.o:
	gcc -Wall -c fconc.c

clean:
	rm *.o

