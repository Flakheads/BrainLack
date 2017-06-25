#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <stack>

#include "program_tree.h"

/*std::ostream& print_error(char* prog_name) {
	return std::cerr
*/

struct Character {
	unsigned character, line;
	char brace;

	Character(unsigned the_char, unsigned the_line, char the_brace)
		: character(the_char), line(the_line), brace(the_brace) {}
};

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
	unsigned char_num = 0, line_num = 1;
	char c;
	std::stack<Character> braces;
	while (src_file >> c) {
		++char_num;
		if (c == '#' || c == '\n') {
			if (c == '#') {
				src_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			char_num = 0;
			++line_num;
		} else if (is_open_brace(c)) {
			just_opened = true;
			braces.push(Character(char_num, line_num, c));
		} else if (is_close_brace(c)) {
			if (braces.empty()) {
				std::cerr << argv[0] << ": unmatched " << c << " at line " << line_num << ", char " << char_num << std::endl;
				break;
			} else if (!is_matching(braces.top().brace, c)) {
				std::cerr << argv[0] << ": mismatched " << braces.top().brace << " at line " << braces.top().line << ", char "
					<< braces.top().character << " and " << c << " at line " << line_num << ", char " << char_num << std::endl;
				break;
			}
			if (just_opened) {
				std::cout << "Found " << braces.top().brace << c << " nilad at " << braces.top().line
					<< ':' << braces.top().character << '-' << line_num << ':' << char_num << std::endl;
			} else {
				std::cout << "Found " << braces.top().brace << c << " monad at " << braces.top().line
					<< ':' << braces.top().character << '-' << line_num << ':' << char_num << std::endl;
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
			std::cerr << argv[0] << ": unmatched " << braces.top().brace << " at line "
				<< braces.top().line << ", char " << braces.top().character << std::endl;
			braces.pop();
		}
	}
	src_file.close();
	return the_err;
}
