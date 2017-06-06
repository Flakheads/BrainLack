#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stack>

#include "program_tree.h"

/*std::ostream& print_error(char* prog_name) {
	return std::cerr
*/

bool is_open_brace(char c) {
	return c == '(' || c == '[' || c == '{' || c == '<';
}

bool is_close_brace(char c) {
	return c == ')' || c == ']' || c == '}' || c == '>';
}

bool is_matching(char b1, char b2) {
	return (b1 == '(' && b2 == ')')
	    || (b1 == '[' && b2 == ']')
	    || (b1 == '{' && b2 == '}')
	    || (b1 == '<' && b2 == '>');
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << argv[0] << ": no input files" << std::endl;
		return 1;
	}
	std::ifstream src_file(argv[1]);
	if (!src_file) {
		std::cerr << argv[0] << ": " << strerror(errno) << std::endl;
		return errno;
	}
	bool just_opened = false;
	unsigned char_num = 0;
	char c;
	std::stack<std::pair<unsigned,char> > braces;
	while (src_file >> c) {
		++char_num;
		if (is_open_brace(c)) {
			just_opened = true;
			braces.push(std::make_pair(char_num,c));
		} else if (is_close_brace(c)) {
			if (braces.empty()) {
				std::cerr << argv[0] << ": unmatched " << c << " at " << char_num << std::endl;
				break;
			} else if (!is_matching(braces.top().second, c)) {
				std::cerr << argv[0] << ": mismatched " << braces.top().second << " at character " << braces.top().first
					<< " and " << c << " at character " << char_num << std::endl;
				break;
			}
			if (just_opened) {
				std::cout << "Found " << braces.top().second << c << " nilad at " << braces.top().first << "-" << char_num << std::endl;
			} else {
				std::cout << "Found " << braces.top().second << "..." << c << " monad at " << braces.top().first << "-" << char_num << std::endl;
			}
			braces.pop();
			just_opened = false;
		}
	}
	int the_err = 0;
	if (src_file) {
		the_err = 1;
	} else if (src_file.bad()) {
		the_err = errno;
		std::cerr << argv[0] << ": " << strerror(errno) << std::endl;
	} else {
		while (!braces.empty()) {
			the_err = 1;
			std::cerr << argv[0] << ": unmatched " << braces.top().second << " at character " << braces.top().first << std::endl;
			braces.pop();
		}
	}
	src_file.close();
	return the_err;
}
