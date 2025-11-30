#include <check.h>
#include <setjmp.h>
#include <signal.h>
#include "buf.h"

static jmp_buf escape;

static void
test_abort_handler(int sig)
{
	longjmp(escape, 1);
}

#suite Buf
#tcase Initialization
#test init_test
	float *a = 0;
	ck_assert_int_eq(buf_capacity(a), 0);
	ck_assert_int_eq(buf_size(a), 0);
	buf_push(a, 1.3f);
	ck_assert_int_eq(buf_size(a), 1);
	ck_assert_float_eq(a[0], 1.3f);
	buf_clear(a);
	ck_assert_int_eq(buf_size(a), 0);
	ck_assert_ptr_ne(a, NULL);
	buf_free(a);
	ck_assert_ptr_eq(a, NULL);

#test clear_empty_test
	float *a = 0;
	buf_clear(a);
	ck_assert_int_eq(buf_size(a), 0);
	ck_assert_ptr_eq(a, NULL);

#tcase Usage
#test push_test
	long *ai = 0;
	for (int i = 0; i < 10000; i++)
		buf_push(ai, i);
	ck_assert_int_eq(buf_size(ai), 10000);
	int match = 0;
	for (int i = 0; i < (int)(buf_size(ai)); i++)
		match += ai[i] == i;
	ck_assert_int_eq(match, 10000);
	buf_free(ai);

#test grow_trunc_test
	long *ai = 0;
	buf_grow(ai, 1000);
	ck_assert_int_eq(buf_capacity(ai), 1000);
	ck_assert_int_eq(buf_size(ai), 0);
	buf_trunc(ai, 100);
	ck_assert_int_eq(buf_capacity(ai), 100);
	buf_free(ai);

#test pop_test
	float *a = 0;
	buf_push(a, 1.1);
	buf_push(a, 1.2);
	buf_push(a, 1.3);
	buf_push(a, 1.4);
	ck_assert_int_eq(buf_size(a), 4);
	ck_assert_float_eq(buf_pop(a), 1.4f);
	buf_trunc(a, 3);
	ck_assert_int_eq(buf_size(a), 3);
	ck_assert_float_eq(buf_pop(a), 1.3f);
	ck_assert_float_eq(buf_pop(a), 1.2f);
	ck_assert_float_eq(buf_pop(a), 1.1f);
	ck_assert_int_eq(buf_size(a), 0);

#suite Failures
#tcase Memory
#test out_of_memory_test
	struct sigaction old_sa;
	struct sigaction sa;

	sigaction(SIGABRT, NULL, &old_sa);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = test_abort_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGABRT, &sa, NULL);

	volatile int aborted = 0;
	int *volatile p = 0;

	if (!setjmp(escape)) {
		size_t max = (PTRDIFF_MAX - sizeof(struct buf)) / sizeof(*p) + 1;
		buf_grow(p, max);
		buf_grow(p, max);
	} else {
		aborted = 1;
	}

	sigaction(SIGABRT, &old_sa, NULL);

	buf_free(p);
	ck_assert_int_eq(aborted, 1);

#test overflow_init_test
	struct sigaction old_sa;
	struct sigaction sa;

	sigaction(SIGABRT, NULL, &old_sa);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = test_abort_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGABRT, &sa, NULL);

	volatile int aborted = 0;
	int *volatile p = 0;

	if (!setjmp(escape)) {
		buf_trunc(p, PTRDIFF_MAX);
	} else {
		aborted = 1;
	}

	sigaction(SIGABRT, &old_sa, NULL);

	buf_free(p);
	ck_assert_int_eq(aborted, 1);

#test overflow_grow_test
	struct sigaction old_sa;
	struct sigaction sa;

	sigaction(SIGABRT, NULL, &old_sa);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = test_abort_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGABRT, &sa, NULL);

	volatile int aborted = 0;
	int *volatile p = 0;

	if (!setjmp(escape)) {
		buf_trunc(p, 1); /* force realloc() use next */
		buf_trunc(p, PTRDIFF_MAX);									
	} else {					
		aborted = 1;			
	}
			
	sigaction(SIGABRT, &old_sa, NULL);

	buf_free(p);	
	ck_assert_int_eq(aborted, 1);
