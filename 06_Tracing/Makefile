GENERATES = move *.so
TRASH = *.o test-* o
CFLAGS = -g -O0 -Wall

move:	move.c protect.c
	$(CC) $(CFLAGS) move.c -o move
	$(CC) $(CFLAGS) -shared protect.c -o protect.so

test:	test-strace test-valid test-preload
	@echo "all tests passed!"

test-strace:	move
	echo "some random text\nQKRQ" > test-1-1
	@cp test-1-1 test-1-cp
	@rm -f test-1-2
	strace -foo -e fault=newfstatat:error=EPERM ./move test-1-1 test-1-2 >/dev/null 2>&1 ; test $$? -eq 2
	@test -e test-1-1
	@test ! -e test-1-2
	@cmp test-1-1 test-1-cp
	@echo "Test 1 passed: stat error handled correctly"
	echo "some random text\nQKRQ" > test-2-1
	@cp test-2-1 test-2-cp
	@rm -f test-2-2
	strace -foo -e fault=openat:error=EACCES:when=3 ./move test-2-1 test-2-2 >/dev/null 2>&1 ; test $$? -eq 3
	@test -e test-2-1
	@test ! -e test-2-2
	@cmp test-2-1 test-2-cp
	@echo "Test 2 passed: open error handled correctly"
	echo "some random text\nQKRQ" > test-3-1
	@cp test-3-1 test-3-cp
	@rm -f test-3-2
	strace -foo -e fault=read:error=EACCES:when=2 ./move test-3-1 test-3-2 >/dev/null 2>&1 ; test $$? -eq 6
	@test -e test-3-1
	@test ! -e test-3-2
	@cmp test-3-1 test-3-cp
	@echo "Test 3 passed: read error handled correctly"
	echo "some random text\nQKRQ" > test-4-1
	@cp test-4-1 test-4-cp
	@rm -f test-4-2
	strace -foo -e fault=close:error=EACCES:when=3 ./move test-4-1 test-4-2 >/dev/null 2>&1 ; test $$? -eq 4
	@test -e test-4-1
	@test ! -e test-4-2
	@cmp test-4-1 test-4-cp
	@echo "Test 4 passed: close error handled correctly"
	echo "some random text\nQKRQ" > test-5-1
	@cp test-5-1 test-5-cp
	@rm -f test-5-2
	strace -foo -e inject=write:retval=-1 ./move test-5-1 test-5-2 >/dev/null 2>&1 ; test $$? -eq 8
	@test -e test-5-1
	@test ! -e test-5-2
	@cmp test-5-1 test-5-cp
	@echo "Test 5 passed: write error handled correctly"
	echo "some random text\nQKRQ" > test-6-1
	@cp test-6-1 test-6-cp
	@rm -f test-6-2
	strace -foo -e fault=unlink:error=EPERM:when=1 ./move test-6-1 test-6-2 >/dev/null 2>&1 ; test $$? -eq 7
	@test -e test-6-1
	@test ! -e test-6-2
	@cmp test-6-1 test-6-cp
	@echo "Test 6 passed: remove error handled correctly"

test-valid:	move
	echo "some random text\nQKRQ" > test-valid-1-1
	@cp test-valid-1-1 test-valid-1-cp
	@rm -f test-valid-1-2
	./move test-valid-1-1 test-valid-1-2 >/dev/null 2>&1
	@test ! -e test-valid-1-1
	@test -e test-valid-1-2
	@cmp test-valid-1-2 test-valid-1-cp
	@echo "Valid test 1 passed"

test-preload:	move protect.so
	echo "some random text\nQKRQ" > test-PROTECT
	@cp test-PROTECT test-protect-1-cp
	@rm -f test-output-1
	LD_PRELOAD=`pwd`/protect.so ./move test-PROTECT test-output-1
	@test -e test-PROTECT
	@test -e test-output-1
	@cmp test-PROTECT test-protect-1-cp
	@cmp test-output-1 test-protect-1-cp
	@echo "Protect test 1 passed"
	echo "some random text\nQKRQ" > test-input
	@cp test-input test-protect-2-cp
	@rm -f test-output-2
	LD_PRELOAD=`pwd`/protect.so ./move test-input test-output-2
	@test ! -e test-input
	@test -e test-output-2
	@cmp test-output-2 test-protect-2-cp
	@echo "Protect test 2 passed"

clean:
	rm -f $(TRASH) $(GENERATES)
