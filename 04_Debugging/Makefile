GENERATES = range
TRASH = *.o test-range-*

range:	range.c
	cc -O0 -g range.c -o range

test:	range
	echo "source range1.gdb" | gdb range | grep @@@ | sed 's/@@@ //g' > test-range-1 2>&1
	echo "source range2.gdb" | gdb range | grep @@@ | sed 's/@@@ //g' > test-range-2 2>&1
	cmp test-range-1 real-range-1
	cmp test-range-2 real-range-2
	@echo "all tests passed!"

clean:
	rm -f $(TRASH) $(GENERATES)
