#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void help() {
	printf("usage: ./move infile outfile\noverwrites infile content into outfile and deletes infile\n");
}

int main(int argc, char **argv) {
	if (argc != 3) {
		help();
		return 1;
	}

	struct stat st;
	if (stat(argv[1], &st)) {
		printf("failed to get infile stat\n");
		return 2;
	}

	int infd;
	if ((infd = open(argv[1], O_RDONLY)) == -1) {
		printf("failed to open infile\n");
		return 3;
	}

	char *buf = malloc(st.st_size);
	if (!buf) {
		printf("failed to allocate memory\n");
		if (close(infd) == -1) {
			printf("failed to close infile\n");
			return 4;
		}
		return 5;
	}

	ssize_t bytes_read = read(infd, buf, st.st_size);
	if (bytes_read != st.st_size) {
		printf("failed to read infile\n");
		free(buf);
		if (close(infd) == -1) {
			printf("failed to close infile\n");
			return 4;
		}
		return 6;
	}

	if (close(infd) == -1) {
		printf("failed to close infile\n");
		free(buf);
		return 4;
	}

	int outfd;
	if ((outfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1) {
		printf("failed to open outfile\n");
		free(buf);
		return 3;
	}

	ssize_t bytes_written = write(outfd, buf, st.st_size);
	if (bytes_written != st.st_size) {
		printf("failed to write into outfile\n");
		free(buf);
		if (close(outfd) == -1) {
			printf("failed to close outfile\n");
			return 4; 
		}
		if (remove(argv[2])) {
			printf("failed to remove outfile\n");
			return 7;
		}
		return 8;
	}

	free(buf);

	if (close(outfd) == -1) {
		printf("failed to close outfile\n");
		return 4;
	}
	
	if (remove(argv[1])) {
		printf("failed to remove infile\n");
		if (remove(argv[2])) {
			printf("failed to remove outfile\n");		                
			return 7;
		}
		return 7;
	}


	return 0;
}
