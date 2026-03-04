#include <iostream>
#include "while_count_utils.h"

namespace while_count_utils{
	int runWhileCount(){
		int upper;
		do {
			std::cout << "Enter a number to count to:" << std::endl;
			std::cin >> upper;
			if (upper > 10){
				std::cout << "I'm programmed to only count up to 10!" << std::endl;
			}
		} while (upper > 10);
		int i = 1;
		while (i <= upper){
			if (i != 5){
				std::cout << i << std::endl;
			}
			i++;
		}
		return 0;
	}
}

