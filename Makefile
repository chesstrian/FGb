OBJS:=main.o file.o helper.o
PROG:=main

all: $(PROG)
default: all

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $@

main.o: main.c
	$(CC) -I lib -c $<

file.o:
	$(CC) -I lib -c lib/file.c

helper.o:
	$(CC) -I lib -c lib/helper.c

clean:
	rm -f $(OBJS)
	rm -f $(PROG)
