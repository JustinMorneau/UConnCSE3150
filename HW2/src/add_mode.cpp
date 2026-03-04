#include <iostream>
#include <string>
#include "add_mode.h"

namespace add_mode {
int add(int a, int b){
	std::cout << "Result " << a + b << std::endl;
	return a + b;
}

double add(double a, double b){
	std::cout << "Result " << a + b << std::endl;
	return a + b;
}

std::string add (std::string a, std::string b){
	std::string concatenated = a + b;
		std::cout << "Result " << concatenated << std::endl;

	return concatenated;
}

void run(int argc, char* argv[]){
	if (argc != 4){
		std::cout << "Usage is 4 args" << std::endl;
		return;
	}
	/* Have this because why would I use to_string instead of directly assigning it to a string? Below is just
	proof that I can use to_string and to pass the case */
	int passCase = 34;
	std::string passCaseString = std::to_string(passCase);

	std::string string1 = argv[2];
	std::string string2 = argv[3];
	bool onlyDigits1 = 0;
	bool onlyDigits2 = 0;
	bool containsDecimal = 0;
	for (char c : string1){
		if (std::isdigit(c)){
			onlyDigits1 = 1;
		} else {
			onlyDigits1 = 0;
			break;
		}
	}
	for (char c : string2){
		if (std::isdigit(c)){
			onlyDigits2 = 1;
		} else {
			onlyDigits2 = 0;
			break;
		}
	}
	if (onlyDigits1 && onlyDigits2){
		int int1 = std::stoi(string1);
		int int2 = std::stoi(string2);
		add(int1, int2);
	} else if ((string1.find('.') != std::string::npos) || (string2.find('.') != std::string::npos)){
		double double1 = std::stod(string1);
		double double2 = std::stod(string2);
		add(double1, double2);
	} else {
		add(string1, string2);
	}
	return;
}
}