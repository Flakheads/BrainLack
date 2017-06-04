#include <iostream>

#include "program_tree.h"

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << argv[0] << ": no input files" << std::endl;
		return 1;
	}
	return 0;
}
