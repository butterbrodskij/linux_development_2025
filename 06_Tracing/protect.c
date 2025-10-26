#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

typedef int (*remove_type)(const char*);

int remove(const char *fname) {
	if (fname && strstr(fname, "PROTECT")) {
		printf("%s is protected from deletion\n", fname);
		return 0;
	}
	remove_type real_remove = dlsym(RTLD_NEXT, "remove");
	return real_remove(fname);
}
