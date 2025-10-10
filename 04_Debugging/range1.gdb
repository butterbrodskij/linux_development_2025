set pagination off

break 30 if i % 5 == 0
	command 1
	printf "@@@ m=%d n=%d s=%d i=%d\n", m, n, s, i
	cont
end

run 1 12 > /dev/null
quit 
