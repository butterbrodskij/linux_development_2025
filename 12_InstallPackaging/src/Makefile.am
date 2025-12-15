if COND_GCOV
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS += -O3 -g3
endif

lib_LTLIBRARIES = libguesser.la
libguesser_la_LDFLAGS = -version-info 1:0:0
bin_PROGRAMS=guesser

guesser_LDADD = libguesser.la

AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"'

maintainer-clean-local:
	rm -f $(DESTDIR)$(bindir)/guesser
	rm -f $(DESTDIR)$(libdir)/libguesser.*

gcov:
	gcov -o .libs libguesser -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
