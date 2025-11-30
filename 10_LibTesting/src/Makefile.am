CFLAGS = -std=c99 -Wall -Wextra -O3 -g3

lib_LTLIBRARIES = libbuf.la
libbuf_la_LDFLAGS = -version-info 1:0:0

bin_PROGRAMS = buf

buf_LDADD = libbuf.la

bench:	buf
	./buf 558d2750ae0e0887

maintainer-clean-local:
	rm -f Makefile.in
	rm -rf .deps

