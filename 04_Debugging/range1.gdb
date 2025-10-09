set pagination off

break 30 if m % 5 == 0
	command 1
	printf "@@@ m=%d n=%d s=%d\n" , m, n, s
	cont
end

run 1 12 >> /dev/null
quit 
