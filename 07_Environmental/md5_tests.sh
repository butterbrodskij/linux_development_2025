#!/bin/sh

if [ ! -x "./rhasher" ]; then
	echo "ERROR: rhasher not found or not executable"
	exit 1
fi

TEST_FILE="test_file_md5.txt"
echo "hello world" > "$TEST_FILE"

compare_hash() {
	local test_name="$1"
	local our_result="$2"
	local expected_result="$3"

	if [ "$our_result" = "$expected_result" ]; then
		echo "PASS: $test_name"
		return 0
	else
		echo "FAIL: $test_name"
		echo "Expected: $expected_result"
		echo "Got: $our_result"
		return 1
	fi
}

OUR_MD5=$(echo "MD5 $TEST_FILE" | ./rhasher)
EXPECTED_MD5=$(md5sum < "$TEST_FILE" | awk '{print $1}')
compare_hash "MD5 file hex" "$OUR_MD5" "$EXPECTED_MD5"

OUR_MD5_BASE64=$(echo "md5 $TEST_FILE" | ./rhasher)
EXPECTED_MD5_BASE64=$(md5sum < "$TEST_FILE" | awk '{print $1}' | xxd -r -p | base64)
compare_hash "MD5 file base64" "$OUR_MD5_BASE64" "$EXPECTED_MD5_BASE64"

OUR_MD5=$(echo 'MD5 "some_random_text' | ./rhasher)
EXPECTED_MD5=$(echo -n "some_random_text" | md5sum | awk '{print $1}')
compare_hash "MD5 string hex" "$OUR_MD5" "$EXPECTED_MD5"

OUR_MD5_BASE64=$(echo 'md5 "some_random_text' | ./rhasher)
EXPECTED_MD5_BASE64=$(echo -n "some_random_text" | md5sum | awk '{print $1}' | xxd -r -p | base64)
compare_hash "MD5 string base64" "$OUR_MD5_BASE64" "$EXPECTED_MD5_BASE64"

rm -f "$TEST_FILE"
