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

	char* new_filebuf = malloc(filesize);
	long new_filesize = filesize;
	int new_i = 0;

	bool sl = false;
	bool ml = false;
	bool star = false;

	for(long i = 0; i < filesize; i++) {
		if(star) {
			if(filebuf[i] == '/') {
				ml =false;

			}
			star = false;
		}
		else if(sl) {
			if(filebuf[i] == '\n') {
				sl = false;
				new_filebuf[new_i] = filebuf[i];
				new_i++;
			} else {
				new_filesize--;
			}
		}
		else if(ml) {
			if(filebuf[i] == '*') {
				star = true;
			}
		}
		else if(filebuf[i] == '/') {
			if(filebuf[i+1] == '/') {
				// Single-line comment, continue to the end of the line
				sl = true;
				new_filesize--;
			}
			else if(filebuf[i] == '*') {
				// Multi-line comment, continue until */
				ml = true;
			}
		}
		else {
			// Not a comment, write to new filebuffer
			new_filebuf[new_i] = filebuf[i];
			new_i++;

		}
	}

	write(new_fd, new_filebuf, new_filesize);
	close(new_fd);

	return 0;
}
