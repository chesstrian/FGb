CC:=gcc

all: main

main: main.o
	$(CC) -o $@ main.o

main.o: main.c
	$(CC) -I ../utils -c $<

clean:
	-rm main main.o
