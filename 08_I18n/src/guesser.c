#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#define MIN_VALUE 0
#define MAX_VALUE 100

int main() {
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALE_PATH);
	textdomain(PACKAGE);

	int a = MIN_VALUE, b = MAX_VALUE, guess;
	printf(_("guess a number from %d to %d\n"), MIN_VALUE, MAX_VALUE);
	char *line = NULL;
	size_t len = 0, read;

	while (a < b) {
		guess = (a + b) / 2;
		printf(_("is your number greater than %d? (Yes/No)\n> "), guess);
		if ((read = getline(&line, &len, stdin)) == -1) {
			printf(_("unexpected EOF\n"));
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
			printf(_("unexpected answer: \"%s\"\n"), line);
		}
	}

	printf(_("your number: %d\n"), a);
	free(line);
	return 0;
}
