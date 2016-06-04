CC = gcc
CFLAGS = -Wall
DEPS =
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main
