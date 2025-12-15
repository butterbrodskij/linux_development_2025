#include <stdio.h>
#include <string.h>
#include "guesser.h"

/** @file libguesser.c
 * Library functions for number conversion.
 */

/** Convert roman number to integer.
 *
 * @param s String representing roman number.
 * @return Corresponding integer value, or 0 if string is invalid.
 */
int from_roman(const char *s) {
	if (!s) {
		return 0;
	}

	int val[256] = {['I']=1, ['i']=1, ['V']=5, ['v']=5, ['X']=10, ['x']=10, ['L']=50, ['l']=50,
			['C']=100, ['c']=100, ['D']=500, ['d']=500, ['M']=1000, ['m']=1000};

	int res = 0, prev = 0;

	for (int i = strlen(s)-1; i >= 0; i--) {
		int cur = val[(unsigned char)s[i]];
		if (!cur) {
			return 0;
		}
		res += cur < prev ? -cur : cur;
		prev = cur;
	}

	return res;
}

/** Convert integer to Roman numeral string.
 * 
 * @param n Number to convert (must be between 1 and 3999 inclusive).
 * @param s Buffer to store result (must be at least MAX_NUM_LEN bytes).
 * @return Pointer to s with Roman numeral representation, or empty string if n is out of valid range.
 */
char *to_roman(int n, char *s) {
	if (n <= 0 || n >= 4000) {
		s[0] = '\0';
		return s;
	}

	static const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

	int len = 0;

	for (int i = 0; i < 13; i++) {
		for (; n >= values[i]; n -= values[i]) {
			const char *sym = symbols[i];
			while (*sym) s[len++] = *sym++;
		}
	}

	s[len] = '\0';

	return s;
}

/** Convert integer to decimal string representation.
 * 
 * @param num Number to convert.
 * @param str Buffer to store result (must be at least MAX_NUM_LEN bytes).
 * @return @p Pointer to str with decimal representation of the number.
 */
char *itoa_default(int num, char *str) {
	snprintf(str, MAX_NUM_LEN, "%d", num);
	return str;
}
