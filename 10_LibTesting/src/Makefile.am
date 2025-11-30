CFLAGS = -std=c99 -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la
libbuf_la_LDFLAGS = -version-info 1:0:0

bin_PROGRAMS = buf

buf_LDADD = libbuf.la

gcov:
	gcov -o .libs libbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'

bench:	buf
	./buf 558d2750ae0e0887

maintainer-clean-local:
	rm -f Makefile.in *.gcno
	rm -rf .deps

