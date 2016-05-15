all: huff.o main.o
	gcc -Wall -w -g -c huff.c main.c

main.o: huff.o main.c
	gcc  -Wall -o main main.c huff.o

huff.o:
	gcc -Wall -o huff.o -c huff.c

clean:
	rm -f *.o main

run:
	./main

zip:
	@zip -r hufman Makefile huff.h huff.c main.c