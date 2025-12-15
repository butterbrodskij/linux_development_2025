TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = dummy upstream
check_PROGRAMS = dummy upstream

CFLAGS += -DBUF_ABORT=test_abort

.ts.c:
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libguesser.la @CHECK_LIBS@

maintainer-clean-local:
	rm -f Makefile.in *.c
	rm -rf .deps
