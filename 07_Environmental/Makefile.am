CFLAGS = -Wall -g -O0

bin_PROGRAMS = rhasher

rhasher_SOURCES = src/rhasher.c
rhasher_LDADD = $(LIBREADLINE)

TESTS = md5_tests.sh sha1_tests.sh error_tests.sh

CLEANFILES = *.txt *.log *.trs

maintainer-clean-local:
	rm -rf autom4te.cache
	rm -f aclocal.m4 compile config.h* configure configure~ install-sh missing
	rm -f Makefile.in depcomp ltmain.sh test-driver
	rm -f *.tar.gz stamp-h1
	rm -rf .deps src/.deps
