#include <preproccessor.h>


int main(int argc, char* argv[]) {
	if(argc < 3) {
		char* msg = "Please supply at least 2 arguments\n";
		write(1, msg, 35);
		return 1;
	}
	char* filename = argv[1];
	char* new_filename = argv[2];

	preproccessor(filename, new_filename);
	
	return 0;
}

