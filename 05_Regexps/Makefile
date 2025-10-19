GENERATES = esub
TRASH = *.o test-*
CFLAGS = -g -O0 -Wall

esub:	esub.c
	$(CC) $(CFLAGS) esub.c -o esub

test:	esub
	echo "current date: 2024 17 October Thursday" | sed -E "s/([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/" > test-sed-1 2>&1
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "current date: 2024 17 October Thursday" > test-esub-1 2>&1
	cmp test-sed-1 test-esub-1
	@echo "all tests passed!"
	
check:	esub
	./esub
	@echo
	./esub "a(b" ab ab ; true
	@echo
	./esub ab "a\1b" ab ; true
	@echo
	./esub ab BA eabc
	@echo
	./esub "a(b)c" "\1_\1" DabcE
	@echo
	./esub "(a)b(c)d(e)" "<\3\2\1>" _abcdef_
	@echo
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "current date: 2024 17 October Thursday"

clean:
	rm -f $(TRASH) $(GENERATES)
