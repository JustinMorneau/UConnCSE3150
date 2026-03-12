#include <iostream>
#include <string>
#include "validation.h"
#include "audit_mode.h"

int main(int argc, char* argv[]){
	if (argc == 3){
		// run file processing
		audit_mode::process_file(argv[1], argv[2]);
		return 0;
	} else {
		// start menu
		int menuMode = 0;
		while (menuMode != 3){
			std::cout << "1. Check a single password\n2. Process a TSV/CSV file\n3. Quit" << std::endl;
			std::cin >> menuMode;
			switch (menuMode) {
				case 1:{
					std::cout << "Enter password: " << std::endl;
					std::cin.ignore();
					std::string password;
					std::getline(std::cin, password);
					bool isValid = validation::is_valid_password(password);
					if (isValid){
						std::cout << "Valid" << std::endl;
					} else {
						std::cout << "Invalid" << std::endl;
					}
					break;
				       }
				case 2:{
					std::string input;
					std::string output;
					std::cin.ignore();
					std::getline(std::cin, input);
					std::getline(std::cin, output);
					audit_mode::process_file(input, output);
					break;
				       }
				case 3:{
					return 0;
					break;
				       }
			}
		}
	}
	return 0;
}
