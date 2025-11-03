#!/bin/sh

if [ ! -x "./rhasher" ]; then
	echo "ERROR: rhasher not found or not executable"
	exit 1
fi

TEST_FILE="test_file_sha1.txt"
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

OUR_SHA1=$(echo "SHA1 $TEST_FILE" | ./rhasher)
EXPECTED_SHA1=$(sha1sum < "$TEST_FILE" | awk '{print $1}')
compare_hash "SHA1 file hex" "$OUR_SHA1" "$EXPECTED_SHA1"

OUR_SHA1_BASE64=$(echo "sha1 $TEST_FILE" | ./rhasher)
EXPECTED_SHA1_BASE64=$(sha1sum < "$TEST_FILE" | awk '{print $1}' | xxd -r -p | base64)
compare_hash "SHA1 file base64" "$OUR_SHA1_BASE64" "$EXPECTED_SHA1_BASE64"

OUR_SHA1=$(echo 'SHA1 "some_random_text' | ./rhasher)
EXPECTED_SHA1=$(echo -n "some_random_text" | sha1sum | awk '{print $1}')
compare_hash "SHA1 string hex" "$OUR_SHA1" "$EXPECTED_SHA1"

OUR_SHA1_BASE64=$(echo 'sha1 "some_random_text' | ./rhasher)
EXPECTED_SHA1_BASE64=$(echo -n "some_random_text" | sha1sum | awk '{print $1}' | xxd -r -p | base64)
compare_hash "SHA1 string base64" "$OUR_SHA1_BASE64" "$EXPECTED_SHA1_BASE64"

rm -f "$TEST_FILE"
