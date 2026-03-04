#include <iostream>
#include <string>
#include "text_mode.h"
#include "add_mode.h"
#include "stats_mode.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		std::cout << "Usage: ./analyzer <mode> [arguments]" << std::endl;
		return 1;
	}
	/* CONTENT HERE */
	std::string str(argv[1]);
	int mode = 0;
	if (str == "text"){
		mode = 1;
	}
	if (str == "add"){
		mode = 2;
	}
	if (str == "stats"){
		mode = 3;
	}
	switch (mode) {
		case 1:
			// text
			text_mode::run(argc, argv);
			break;
		case 2:
			// add
			add_mode::run(argc, argv);
			break;
		case 3:
			// stats
			stats_mode::run(argc, argv);
			break;
		default:
			// not an option
			std::cout << "Invalid mode" << std::endl;
			return 1;
	}
	return 0;
}
