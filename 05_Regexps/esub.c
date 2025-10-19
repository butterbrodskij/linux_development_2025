#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10
#define BUF_SIZE 1024

void help() {
	printf("usage: ./esub regexp substitution string\nprints echo 'string' | sed -E 's/regexp/substitution/'\n");
	return;
}

int main(int argc, char **argv) {
	if (argc < 4) {
		help();
		return 0;
	}
	
	char buffer[BUF_SIZE];
	regex_t regex;
	int t;
	if ((t = regcomp(&regex, argv[1], REG_EXTENDED)) != 0) {
		regerror(t, &regex, buffer, sizeof(buffer));
		fprintf(stderr, "failed to compile regular expression: %s\n", buffer);
		return 1;
	}

	regmatch_t bags[MAXGR];
	if (regexec(&regex, argv[3], MAXGR, bags, 0) == 0) {
		int res_size = (bags[0].rm_so+1 > BUF_SIZE) ? bags[0].rm_so+1 : BUF_SIZE;
		char *res = malloc(res_size);
		if (res == NULL) {
			fprintf(stderr, "failed to allocate memory\n");
			regfree(&regex);
			return 1;
		}

		strncpy(res, argv[3], bags[0].rm_so);

		int res_len = bags[0].rm_so, str_len = strlen(argv[2]);
		
		for (int i = 0; i < str_len; i++) {
			if (argv[2][i] == '\\' && i < str_len-1 && argv[2][i+1] >= '0' && argv[2][i+1] <= '9') {
				i++;
				int num = argv[2][i] - '0';
				if (num >= MAXGR || bags[num].rm_so < 0) {
					fprintf(stderr, "unexpected window number: %d\n", num);
					regfree(&regex);
					free(res);
					return 1;
				}
				
				int add_len = bags[num].rm_eo - bags[num].rm_so;
				if (res_len + add_len + 1 >= res_size) {
					res_size = (res_len + add_len + 1) * 2;
					if ((res = realloc(res, res_size)) == NULL) {
						fprintf(stderr, "failed to allocate enough memory\n");
						regfree(&regex);
						return 1;
					}
				}

				strncpy(res + res_len, argv[3]+bags[num].rm_so, bags[num].rm_eo - bags[num].rm_so);
				res_len += bags[num].rm_eo - bags[num].rm_so;
			} else {
				res[res_len++] = argv[2][i];
				if (res_len >= res_size) {
					res_size *= 2;
					if ((res = realloc(res, res_size)) == NULL) {
						fprintf(stderr, "failed to allocate enough memory\n");
						regfree(&regex);
						return 1;
					}
				}
			}
		}

		res[res_len] = '\0';
		printf("%s%s\n", res, argv[3] + bags[0].rm_eo);
		free(res);
	} else {
		printf("%s\n", argv[3]);
	}

	regfree(&regex);
	return 0;
}
