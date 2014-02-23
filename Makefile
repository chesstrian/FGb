CC:=gcc
CPP:=g++ 

SRC:=src
LIB:=lib
ARCH:=x64
DIR_FGB:=fgb

CFLAGS:=-std=gnu99 -m64 -g

LINKS:=-lfgb -lfgbexp -lgb -lgbexp -lminpoly -lgmp -lminpolyvgf -lm -fopenmp

OBJS:=main.o file.o helper.o utilities.o str.o
PROG:=main

all: $(PROG)
default: all

$(PROG): $(OBJS)
	$(CPP) $(OBJS) -o $@ -I $(DIR_FGB) -L $(DIR_FGB)/$(ARCH) $(LINKS) 

main.o: $(SRC)/main.c
	$(CC) -I $(LIB) -I $(DIR_FGB) -I $(DIR_FGB)/nv/protocol -I $(DIR_FGB)/nv/int -c $<

%.o: $(LIB)/%.c
	$(CC) -I $(LIB) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)
	rm -f $(PROG)

test: main
	./main ./resources/inputs/InputPolinomials.txt 1
