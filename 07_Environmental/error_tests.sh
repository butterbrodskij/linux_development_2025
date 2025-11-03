#!/bin/sh

if [ ! -x "./rhasher" ]; then
	echo "ERROR: rhasher not found or not executable"
	exit 1
fi

check_error_output() {
	local test_name="$1"
	local command="$2"
	local error_output
	error_output=$(echo "$command" | ./rhasher 2>&1 > /dev/null)

	if [ -n "$error_output" ]; then
		echo "PASS: $test_name (stderr: '$error_output')"
		return 0
	else
		echo "FAIL: $test_name - expected error message but stderr is empty"
		return 1
	fi
}

check_error_output "Unknown algorithm" "INVALID_ALG test"

check_error_output "Missing target" "MD5"

check_error_output "Non-existent file" "MD5 /path/to/nonexistent/file"
