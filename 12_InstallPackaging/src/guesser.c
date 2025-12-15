/** @mainpage Number guessing game with binary search algorithm.
 * @copydetails guesser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include <libintl.h>
#include <locale.h>
#include "guesser.h"

#define _(STRING) gettext(STRING) /**< Macro for internationalization */

/** @file guesser.c
 * Main file for the number guessing game.
 */

/** @page guesser
 * Number guessing game with binary search algorithm.
 * @section SYNOPSIS
 * `guesser` [ **-r** | **--roman** ] [ **-h** | **--help** ]
 *
 * @section DESCRIPTION
 * The program guesses a number between MIN_VALUE and MAX_VALUE
 * using binary search algorithm. It asks yes/no questions until
 * the number is found.
 * @section OPTIONS
 * - **-r**, **--roman**: Use Roman numerals instead of Arabic
 * - **-h**, **--help**: Display help message and exit
 */

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

/** Main function of the number guessing game
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return 0 on success, 1 on error
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
