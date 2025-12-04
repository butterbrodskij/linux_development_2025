#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

/** @file guesser.c
 * Number guessing game with binary search algorithm.
 *
 * The program guesses a number between MIN_VALUE and MAX_VALUE
 * by asking yes/no questions. Supports both Arabic and Roman numerals.
 */

/* Program limitations */
#define MIN_VALUE 1    /**< Minimum number that can be guessed */
#define MAX_VALUE 3999 /**< Maximum number that can be guessed */
#define MAX_NUM_LEN 17 /**< Maximum lenght of string represantation of numbers */

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

/** Callback type for number formatting (Arabic/Roman numerals). */
typedef char *(itoa_func)(int, char*);

/** Print usage information.
 *
 * @param file_name Name of the executable (argv[0]).
 */
void help(char *file_name) {
	printf(_("Usage: %s [OPTION]\n"), file_name);
	printf(_("Guess the number game using binary search algorithm.\n\n"));
	printf(_("Options:\n"));
	printf(_("  -h, --help     display this help and exit\n"));
	printf(_("  -r, --roman    use Roman numerals instead of Arabic\n\n"));
	printf(_("Description:\n"));
	printf(_("  The program will try to guess your number between %d and %d\n"), MIN_VALUE, MAX_VALUE);
	printf(_("  by asking questions. Answer with 'yes'/'no' or 'y'/'n' (also supports Russian).\n\n"));
}


/** @page guesser
 * Number guessing game with binary search algorithm.
 *
 * @section SYNOPSIS
 * `guesser` [ \a -r ]
 * @section DESCRIPTION
 * The program guesses a number between MIN_VALUE and MAX_VALUE
 * by asking yes/no questions. Supports both Arabic and Roman numerals.
 */
int main(int argc, char **argv) {
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALE_PATH);
	textdomain(PACKAGE);

	char str_num1[MAX_NUM_LEN], str_num2[MAX_NUM_LEN];
	itoa_func *itoa_f = itoa_default;

	if (argc >= 2) {
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			help(argv[0]);
			return 0;
		}
		if (!strcmp(argv[1], "-r") || !strcmp(argv[1], "--roman")) {
			itoa_f = to_roman;
		} else {
			fprintf(stderr, _("Error: Unknown option '%s'\n"), argv[1]);
			fprintf(stderr, _("Try '%s --help' for more information.\n"), argv[0]);
			return 1;
		}
	}

	int a = MIN_VALUE, b = MAX_VALUE, guess;
	printf(_("guess a number from %s to %s\n"), itoa_f(MIN_VALUE, str_num1), itoa_f(MAX_VALUE, str_num2));
	char *line = NULL;
	size_t len = 0, read;

	while (a < b) {
		guess = (a + b) / 2;
		printf(_("is your number greater than %s? (Yes/No)\n> "), itoa_f(guess, str_num1));
		if ((read = getline(&line, &len, stdin)) == -1) {
			fprintf(stderr, _("unexpected EOF\n"));
			free(line);
			return 1;
		}

		if (line[read - 1] == '\n') {
			line[read - 1] = '\0';
		}

		for (char *c = line; *c; ++c) *c = tolower(*c);

		if (!strcmp(line, "yes") || !strcmp(line, "y") || !strcmp(line, "да") || !strcmp(line, "д")) {
			a = guess + 1;
		} else if (!strcmp(line, "no") || !strcmp(line, "n") || !strcmp(line, "нет") || !strcmp(line, "н")) {
			b = guess;
		} else {
			fprintf(stderr, _("unexpected answer: \"%s\"\n"), line);
		}
	}

	printf(_("your number: %s\n"), itoa_f(a, str_num1));
	free(line);
	return 0;
}
