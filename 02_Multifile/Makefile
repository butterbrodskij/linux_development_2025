.PHONY: all clean distclean
CFLAGS = -Wall
GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so test-prog-*

all:	README prog prog-a prog-so test

liboutput_static.a:	liboutput_static.a(fun.o const.o)

prog-a:	prog.o liboutput_static.a
	$(CC) -o $@ prog.o -L. -loutput_static

liboutput.so:	fun.o const.o
	$(CC) -shared $^ -o $@

prog-so:	prog.o liboutput.so
	$(CC) -o $@ prog.o -L. -loutput

prog:	const.o fun.o prog.o

README:	prog
	./$< 2> $@

fun.o prog.o:	outlib.h

test:	prog prog-a prog-so
	./prog > test-prog-noarg 2>&1
	./prog-a > test-prog-a-noarg 2>&1
	LD_LIBRARY_PATH=. ./prog-so > test-prog-so-noarg 2>&1
	cmp test-prog-noarg test-prog-a-noarg
	cmp test-prog-a-noarg test-prog-so-noarg

	./prog param1 > test-prog-onearg 2>&1
	./prog-a param1 > test-prog-a-onearg 2>&1
	LD_LIBRARY_PATH=. ./prog-so param1 > test-prog-so-onearg 2>&1
	cmp test-prog-onearg test-prog-a-onearg
	cmp test-prog-a-onearg test-prog-so-onearg

	./prog param1 param2 param3 > test-prog-threearg 2>&1
	./prog-a param1 param2 param3 > test-prog-a-threearg 2>&1
	LD_LIBRARY_PATH=. ./prog-so param1 param2 param3 > test-prog-so-threearg 2>&1
	cmp test-prog-threearg test-prog-a-threearg
	cmp test-prog-a-threearg test-prog-so-threearg

	@echo "all tests passed!"

clean:
	rm -f $(TRASH) $(GENERATES)