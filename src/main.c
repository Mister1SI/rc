#include <preproccessor.h>


int main(int argc, char* argv[]) {
	if(argc < 3) {
		char* msg = "Please supply at least 2 arguments\n";
		write(1, msg, 35);
		return 1;
	}
	char* filename = argv[1];
	char* new_filename = argv[2];

	int preproccessor_result = preproccessor(filename, new_filename);
	if(preproccessor_result != 0) {
		char* msg = "Preproccessor Error\n";
		write(1, msg, 20);
		return 1;
	}

	return 0;
}

