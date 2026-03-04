#include <iostream>
#include "string_utils.h"
#include <string>

namespace string_utils{
	/*
	 The function reads in an integer for string length, which
	 prints an error message if it is 20 or larger while signaling
	 to main to return 1. Otherwise, it removes the newline character
	 using cin.ignore(), and then prompts the user to enter a string.
	 it reads the full line using std::getline which works correctly
	 as we ignore the newline after the extraction >> operator. It
	 creates a character array of size 20 and copies the characters
	 to the array one at a time, and puts a null terminator at the end.
	 Afterwards, it prints the string.
	 */
	int runStringOption(){
		int strlen;
		std::string uin;
		std::cout << "Enter string length:" << std::endl;
		std::cin >> strlen;
		if (strlen >= 20){
			std::cout << "Error:" << " must be less than 20" << std::endl;
			return 1;
		}
		std::cin.ignore();
		std::cout << "Enter string:" << std::endl;
		std::getline(std::cin, uin);
		char arry[20];
		if (strlen != 0){
			for (int i = 0; i < strlen; i++){
				arry[i] = uin[i];
			}
			arry[strlen] = '\0';
		} else {
			arry[0] = '\0';
		}
		std::cout << "C-style string: " << arry << std::endl;
		return 0;
	}
}

