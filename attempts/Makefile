CFLAGS=-Wall -Werror -g -ansi -pedantic -std=c89
CCFLAGS=-Wall -Werror -g
LDFLAGS=-g -Wall -lstdc++

OBJS:=main.o utils.o UtilsWrapper.o Utils.o
PROG:=main

all: $(PROG)
default: all

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

main.o: main.c
	$(CC) -I ../utils -I ../cpp -c $<

utils.o:
	$(CC) -I ../utils -c ../utils/utils.c

UtilsWrapper.o:
	$(CC) -I ../cpp $(CCFLAGS) -c ../cpp/UtilsWrapper.cc

Utils.o:
	$(CC) -I ../cpp $(CCFLAGS) -c ../cpp/Utils.cc

clean:
	rm -f $(OBJS)
	rm -f $(PROG)
