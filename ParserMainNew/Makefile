CC = gcc
CFLAGS = -Wall -O3
DEPS = AuxiliarFunction.h
OBJ = main.o AuxiliarFunction.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main
