CC = gcc
CFLAGS = -pedantic -Wall -Wextra
main: main.c
	$(CC) main.c -o main.o $(CFLAGS)
	chmod 755 main.o

clean:
	rm *.o