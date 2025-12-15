#include <check.h>
#include "guesser.h"

char s[MAX_NUM_LEN];

#suite Guesser
#tcase FromRoman
#test single_letter_test
	ck_assert_int_eq(from_roman("I"), 1);
	ck_assert_int_eq(from_roman("V"), 5);
	ck_assert_int_eq(from_roman("X"), 10);
	ck_assert_int_eq(from_roman("L"), 50);
	ck_assert_int_eq(from_roman("C"), 100);
	ck_assert_int_eq(from_roman("D"), 500);
	ck_assert_int_eq(from_roman("M"), 1000);

#test many_letters_test
	ck_assert_int_eq(from_roman("VII"), 7);
	ck_assert_int_eq(from_roman("XXIV"), 24);
	ck_assert_int_eq(from_roman("CDLVI"), 456);
	ck_assert_int_eq(from_roman("MCCXXXIV"), 1234);

#tcase ToRoman
#test digit_test
	ck_assert_str_eq(to_roman(1, s), "I");
	ck_assert_str_eq(to_roman(3, s), "III");
	ck_assert_str_eq(to_roman(5, s), "V");
	ck_assert_str_eq(to_roman(7, s), "VII");
	ck_assert_str_eq(to_roman(9, s), "IX");

#test number_test
	ck_assert_str_eq(to_roman(12, s), "XII");
	ck_assert_str_eq(to_roman(78, s), "LXXVIII");
	ck_assert_str_eq(to_roman(392, s), "CCCXCII");
	ck_assert_str_eq(to_roman(888, s), "DCCCLXXXVIII");
	ck_assert_str_eq(to_roman(3888, s), "MMMDCCCLXXXVIII");

#tcase FromToEqual
#test from_to_test
	ck_assert_str_eq(to_roman(from_roman("XII"), s), "XII");
	ck_assert_str_eq(to_roman(from_roman("CCCLVII"), s), "CCCLVII");
	ck_assert_str_eq(to_roman(from_roman("DCCLXV"), s), "DCCLXV");
	ck_assert_str_eq(to_roman(from_roman("MCCXXXIV"), s), "MCCXXXIV");
	ck_assert_str_eq(to_roman(from_roman("MMMCMXCIX"), s), "MMMCMXCIX");

#test to_from_test
	ck_assert_int_eq(from_roman(to_roman(17, s)), 17);
	ck_assert_int_eq(from_roman(to_roman(177, s)), 177);
	ck_assert_int_eq(from_roman(to_roman(761, s)), 761);
	ck_assert_int_eq(from_roman(to_roman(2899, s)), 2899);

#tcase ItoaDefault
#test smoke_test
	ck_assert_str_eq(itoa_default(12, s), "12");
	ck_assert_str_eq(itoa_default(123, s), "123");
	ck_assert_str_eq(itoa_default(123456, s), "123456");

#suite Failure
#tcase FromRomanFailure
#test invalid_symbols_test
	ck_assert_int_eq(from_roman("QKRQ"), 0);
	ck_assert_int_eq(from_roman("aboba"), 0);

#test empty_string_test
	ck_assert_int_eq(from_roman(NULL), 0);

#tcase ToRomanFailure
#test invalid_number_test
	ck_assert_str_eq(to_roman(0, s), "");
	ck_assert_str_eq(to_roman(-100, s), "");
	ck_assert_str_eq(to_roman(4000, s), "");
