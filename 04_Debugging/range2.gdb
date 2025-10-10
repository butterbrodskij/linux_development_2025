set pagination off

set $i=0

break 30 if ++$i >= 28 && $i <= 35
	command 1
	printf "@@@ m=%d n=%d s=%d i=%d\n" , m, n, s, i
	cont
end

run -100 100 3 > /dev/null
quit
