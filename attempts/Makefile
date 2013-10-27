CC:=gcc

OBJS:=main.o utils.o
PROG:=main

all: $(PROG)
default: all

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $@

utils.o:
	$(CC) -I ../utils -c ../utils/utils.c

%.o: %.c
	$(CC) -I ../utils -c $<

clean:
	rm -f $(OBJS)
	rm -f $(PROG)
