CFLAGS := -m64 -g
CC:=gcc $(CFLAGS)
CPP:=g++ $(CFLAGS)
LIBDIR := x64

bug_main:bug_main.o bug_prog1.o  bug_prog2.o
	$(CPP) -o $@ bug_main.o bug_prog1.o bug_prog2.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lgmp -lminpolyvgf -lm -fopenmp

bug_main.static:bug_main.o bug_prog1.o  bug_prog2.o
	$(CPP) -static -o $@ bug_main.o bug_prog1.o bug_prog2.o -L$(LIBDIR) -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -L$(GMP_STATIC_DIR) -lgmp -lm -fopenmp

bug_main.o:bug_main.c
	$(CC) -I ./nv/protocol -I ./nv/int  -c $<

bug_prog1.o:bug_prog1.c
	$(CC) -I ./nv/protocol -I ./nv/int  -c $<

bug_prog2.o:bug_prog2.c
	$(CC) -I ./nv/protocol -I ./nv/int  -c $<

clean:
	-rm bug_main bug_main.o bug_prog2.o bug_prog1.o

veryclean:
	-rm bug_main bug_main.o bug_prog2.o bug_prog1.o *~

test:bug_main
	@echo "======================================================================"
	./bug_main 1
	@echo "======================================================================"

