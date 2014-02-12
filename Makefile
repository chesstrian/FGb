ifndef CC
	CC = gcc
endif

SRC:=src
LIB:=lib

CFLAGS:=-std=gnu99

OBJS:=main.o file.o helper.o utilities.o str.o
PROG:=main

all: $(PROG)
default: all

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $@

main.o: $(SRC)/main.c
	$(CC) -I $(LIB) -c $<

%.o: $(LIB)/%.c
	$(CC) -I $(LIB) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)
	rm -f $(PROG)
