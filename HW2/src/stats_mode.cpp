#include <iostream>
#include <string>
#include <cctype>
#include "stats_mode.h"

namespace stats_mode {
void run(int argc, char* argv[]){
    if (argc < 3){
        std::cout << "Usage is 3 args" << std::endl;
        return;
    }
	std::string str;
	for (int i = 2; i < argc; i++){
		str += argv[i];
		if (i < argc - 1){
			str += " ";
		}
	}
    size_t strLen = str.size();
    std::cout << "Length " << strLen << std::endl;
    int arry[strLen];
    bool seen[256] = {false};
    int uniqueChars = 0;
    for (char c : str){
        if (!seen[(unsigned char) c]){
            seen[(unsigned char) c] = true;
            uniqueChars++;
        }
    }
    std::cout << "Unique " << uniqueChars << std::endl;
    bool onlyAlphanumeric = false;
    for (int i = 0; i < strLen; i++){
        if (std::isalnum(str[i])){
            onlyAlphanumeric = true;
        } else {
            onlyAlphanumeric = false;
            break;
        }
    }
    if (onlyAlphanumeric){
        std::cout << "Alphanumeric Yes" << std::endl;
    } else {
        std::cout << "Alphanumeric No" << std::endl;
    }
    std::string copyString = str;
    for (int i = 0; i < strLen/2; i++){
        char temp;
        temp = str[i];
        str[i] = str[strLen - i - 1];
        str[strLen - i - 1] = temp;
    }
    std::cout << "Reversed " << str << std::endl;
    std::string copyString2;
    for (char c : copyString){
        if (c != ' '){
            copyString2 += c;
        }
    }
    std::cout << "Without spaces " << copyString2 << std::endl;
    // Palindrome check
    for (size_t i = 0; i < strLen; i++){
        str[i] = std::tolower(str[i]);
    }
    std::string palindromeString;
    for (char c : str){
        if (c != ' '){
            palindromeString += c;
        }
    }
    size_t palSize = palindromeString.size();
    std::string backwardsPalindrome = palindromeString;
    for (int i = 0; i < palSize/2; i++){
        char temp;
        temp = backwardsPalindrome[i];
        backwardsPalindrome[i] = backwardsPalindrome[palSize - i - 1];
        backwardsPalindrome[palSize - i - 1] = temp;
    }
    if (palindromeString == backwardsPalindrome){
        std::cout << "Palindrome Yes" << std::endl;
    } else {
        std::cout << "Palindrome No" << std::endl;
    }
    return;
}
}