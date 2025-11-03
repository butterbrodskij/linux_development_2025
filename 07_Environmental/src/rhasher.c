#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "rhash.h"
#include <unistd.h>
#include "config.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

int get_hash_id(const char *name) {
	char name_lower[5];
	strncpy(name_lower, name, sizeof(name_lower));
	name_lower[sizeof(name_lower) - 1] = '\0';
	for (int i = 0; i < strlen(name_lower); i++) {
		name_lower[i] = tolower(name_lower[i]);
	}
	if (!strcmp(name_lower, "md5")) {
		return RHASH_MD5;
	}
	if (!strcmp(name_lower, "sha1")) {
		return RHASH_SHA1;
	}
	if (!strcmp(name_lower, "tth")) {
		return RHASH_TTH;
	}
	return 0;
}

int hash_string(const char *msg, int hash_id, const char *hash_str, char *output) {
	unsigned char digest[64];

	int res = rhash_msg(hash_id, msg, strlen(msg), digest);
	if (res < 0) {
		return 1;
	}

	if (hash_str && *hash_str <= 'Z' && *hash_str >= 'A') {
		rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), RHPR_HEX);
	} else {
		rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), RHPR_BASE64);
	}

	return 0;
}

int hash_file(const char *filepath, int hash_id, const char *hash_str, char *output) {
	unsigned char digest[64];

	int res = rhash_file(hash_id, filepath, digest);
	if (res < 0) {
		return 1;
	}

	if (hash_str && *hash_str <= 'Z' && *hash_str >= 'A') {
		rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), RHPR_HEX);
	} else {
		rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), RHPR_BASE64);
	}

	return 0;
}

int main() {
	char *line = NULL;
#ifndef USE_READLINE
	size_t len = 0;
	size_t read;
#endif

	rhash_library_init();

	int interactive = isatty(STDIN_FILENO);

#ifdef USE_READLINE
	FILE *devnull = NULL;
	if (!interactive) {
		devnull = fopen("/dev/null", "w");
		if (devnull) {
			rl_outstream = devnull;
		} else {
			rl_outstream = stderr;
		}
	}
	const char *intro = interactive ? ">> " : NULL;
	while ((line = readline(intro))) {
		if (!strlen(line)) {
			continue;
		}
		add_history(line);
#else
	if (interactive) {
		printf("> ");
	}
	while ((read = getline(&line, &len, stdin)) != -1) {
		if (line[read - 1] == '\n') {
			line[read - 1] = '\0';
		}
		if (!strlen(line)) {
			if (interactive) {
				printf("> ");
			}
			continue;
		}
#endif

		char *alg = strtok(line, " ");
		if (!alg) {
			fprintf(stderr, "expected algorithm name\n");
#ifdef USE_READLINE
			free(line);
#else
			if (interactive) {
				printf("> ");
			}
#endif
			continue;
		}

		char *target = strtok(NULL, " ");
		if (!target) {
			fprintf(stderr, "expected target (file or word starting with \")\n");
#ifdef USE_READLINE
			free(line);
#else
			if (interactive) {
				printf("> ");
			}
#endif
			continue;
		}

		int hash_id = get_hash_id(alg);
		if (!hash_id) {
			fprintf(stderr, "unexpected algorithm name\nsupported algorithms: md5, sha1, tth\n");
#ifdef USE_READLINE
			free(line);
#else	
			if (interactive) {
				printf("> ");
			}
#endif
			continue;
		}

		char res[130] = "";
		if (*target == '"') {
			if (hash_string(target + 1, hash_id, alg, res)) {
				fprintf(stderr, "hashing string failed\n");
#ifdef USE_READLINE
				free(line);
#else
				if (interactive) {
					printf("> ");
				}
#endif
				continue;
			}
		} else {
			if (hash_file(target, hash_id, alg, res)) {
				fprintf(stderr, "hashing file failed\n");
#ifdef USE_READLINE
				free(line);
#else
				if (interactive) {
					printf("> ");
				}
#endif
				continue;
			}
		}

		printf("%s\n", res);
#ifdef USE_READLINE
		free(line);
#else
		if (interactive) {
			printf("> ");
		}
#endif
	}

#ifndef USE_READLINE
	free(line);
#else
	if (devnull) {
		fclose(devnull);
	}
#endif

	return 0;
}
