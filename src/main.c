#include <preproccessor.h>

#include <sys/file.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	if(argc < 3) {
		char* msg = "Please supply at least 2 arguments\n";
		write(1, msg, 35);
		return 1;
	}
	char* filename = argv[1];
	char* destination = argv[2];
	char* tmp_filename = "/tmp/.rc-tmp"; // 12 chars

	int preproccessor_result = preproccessor(filename, tmp_filename);
	if(preproccessor_result != 0) {
		char* msg = "Preproccessor Error\n";
		write(1, msg, 20);
		return 1;
	}

	int tmp_fd = open(tmp_filename, O_RDONLY, 00644);
	if(tmp_fd == -1) {
		char* msg = "File error\n";
		write(1, msg, 11);
		return 1;
	}
	
	struct stat st;
	fstat(tmp_fd, &st);
	long tmp_filesize = st.st_size;

	char* filebuf = malloc(tmp_filesize);
	read(tmp_fd, filebuf, tmp_filesize);
	close(tmp_fd);

	int new_fd = open(destination, O_CREAT | O_WRONLY, 00644);
	if(new_fd == -1) {
		write(1, "File error\n", 11);
		return 1;
	}

	write(new_fd, filebuf, tmp_filesize);
	close(new_fd);

	return 0;
}

