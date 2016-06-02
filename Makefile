all: huff.o main.o funcao.o
	gcc -Wall -w -g -c huff.c funcao.c main.c

main.o: huff.o main.c
	gcc  -Wall -o main main.c funcao.o huff.o

funcao.o: funcao.h huff.o
	gcc -Wall -o funcao.o -c funcao.c huff.o

huff.o:
	gcc -Wall -o huff.o -c huff.c

clean:
	rm -f *.o main

run:
	./main

zip:
	@zip -r hufman Makefile huff.h huff.c main.c