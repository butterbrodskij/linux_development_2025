SUBDIRS = po src

CFLAGS = -Wall -g -O0

CLEANFILES = *.txt *.log *.trs

run-ru:
	LANG=ru_RU.UTF-8 LC_ALL=ru_RU.UTF-8 $(DESTDIR)$(bindir)/guesser

run-en:
	LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8 $(DESTDIR)$(bindir)/guesser

maintainer-clean-local:
		rm -rf autom4te.cache
		rm -f aclocal.m4 compile config.h* configure configure~ install-sh missing
		rm -f Makefile.in depcomp ltmain.sh test-driver
		rm -f *.tar.gz stamp-h1
		rm -rf .deps src/.deps m4
		rm -f src/Makefile.in config.* ABOUT-NLS
		rm -rf $(DESTDIR)$(localedir)
		rm -f po/*.header po/*.sin po/*.template po/*.sed po/ru.po~ po/Rules-quot po/Makefile.in.in po/LINGUAS
