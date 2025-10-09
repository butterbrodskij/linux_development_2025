#include <stdio.h>
#include <stdlib.h>

void help() {
	printf("usage: ./range [M=0] N [S=1]\nprints sequence [M, M+S, M+2S, … N-1]\n");
	return;
}

int main(int argc, char **argv) {
	int n, m = 0, s = 1;
	switch (argc) {
		case 2:
			n = atoi(argv[1]);
			break;
		case 3:
			m = atoi(argv[1]);
			n = atoi(argv[2]);
			break;
		case 4:
			m = atoi(argv[1]);
			n = atoi(argv[2]);
			s = atoi(argv[3]);
			break;
		default:
			help();
			return 0;
	}

	for (; m < n; m += s) {
		printf("%d\n", m);
	}

	return 0;
}
