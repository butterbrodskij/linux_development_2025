bin_PROGRAMS=guesser
guesser_SOURCES = guesser.c
AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"'

all-local:	guesser$(EXEEXT)
	LC_ALL=C ./guesser -h | ./convert_to_md.sh > $(srcdir)/title.md

maintainer-clean-local:
	rm -f $(DESTDIR)$(bindir)/guesser
	rm -f $(srcdir)/title.md
