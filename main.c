#include <sys/file.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
	if(argc < 3) {
		char* msg = "Please supply at least 2 arguments\n";
		write(1, msg, 35);
		return 1;
	}
	char* filename = argv[1];
	size_t filename_size = strlen(filename);
	
	char* new_filename = argv[2];
	size_t new_filename_size = strlen(new_filename);

	int fd = open(filename, O_RDWR, 00644);
	if(fd == -1) {
		char* msg = "Failed to open file ";
		char* n = "\n";
		write(1, msg, 20);
		write(1, filename, filename_size);
		write(1, n, 1);
		return 1;
	}
	
	int new_fd = open(new_filename, O_WRONLY | O_CREAT, 00644);
	if(fd == -1) {
		char* msg = "Failed to create new file ";
		char* n = "\n";
		write(1, msg, 26);
		write(1, new_filename, new_filename_size);
		write(1, n, 1);
		return 1;
	}

	struct stat st;
	fstat(fd, &st);
	long filesize = (long) st.st_size;

	char* filebuf = malloc(filesize);
	read(fd, filebuf, filesize);
	close(fd);
	
	bool sl = false;
	bool ml = false;

	for(long i = 0; i < filesize; i++) {
		char a = *(filebuf + i);

		if(sl) {
			if(a == '\n') {
				sl = false;
			} else {
				a = 'e';
			}
		}
		else if(ml) {

		}
		else if(a == '/') {
			if(a == '/') {
				// Single-line comment, continue to the end of the line
				sl = true;
			}
			else if(a == '*') {
				// Multi-line comment, continue until */
			}
			else {
				// Not a comment, ignore
			}
		}
	}

	write(new_fd, filebuf, filesize);
	close(new_fd);

	return 0;
}
