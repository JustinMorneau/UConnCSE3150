#include <iostream>
#include <string>
#include <cctype>
#include "text_mode.h"

namespace text_mode{
void run(int argc, char* argv[]){
	if (argc < 3){
		std::cout << "Usage is at least 3 args" << std::endl;
		return;
	}
	std::string newString;
	for (int i = 2; i < argc; i++){
		newString += argv[i];
		if (i < argc - 1){
			newString += " ";
		}
	}
	std::cout << "Original " << newString << std::endl;
	size_t strLen = newString.size();
	std::cout << "Length: " << strLen << std::endl;
	int Letters = 0;
	int Digits = 0;
	int Spaces = 0;
	int Punctuation = 0;
	for (size_t i = 0; i < strLen; i++){
		if (std::isalpha(newString[i])){
			Letters += 1;
		}
		if (std::isdigit(newString[i])){
			Digits += 1;
		}
		if (std::isspace(newString[i])){
			Spaces += 1;
		}
		if (std::ispunct(newString[i])){
			Punctuation += 1;
		}
	}
	std::cout << "Letters: " <<Letters << std::endl;
	std::cout << "Digits: " << Digits << std::endl;
	std::cout << "Spaces: " << Spaces << std::endl;
	std::cout << "Punctuation: " << Punctuation << std::endl;
	std::string copyStringUpper = "";
	for (char c : newString){
		copyStringUpper += std::toupper(c);
	}
	std::cout << "Uppercase " <<copyStringUpper << std::endl;
	for (size_t i = 0; i < strLen; i++){
		newString[i] = std::tolower(newString[i]);
	}
	std::cout << "Lowercase : " << newString << std::endl;
	if (newString.find("test")!= std::string::npos){
		std::cout << "containstestyes" << std::endl;
	} else {
		std::cout << "containstestno" << std::endl;
	}
	size_t pos = newString.find(' ');
	if (pos != std::string::npos){
		std::cout << "First word: " << newString.substr(0, pos) << std::endl;
	} else {
		std::cout << "Nah fam" << newString << std::endl;
	}
	return;
}
}