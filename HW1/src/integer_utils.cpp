#include <iostream>
#include "integer_utils.h"

namespace integer_utils{
	int runIntegerOption(){
		int a;
		int b;
		double da;
		std::cout << "Enter first integer:" << std::endl;
		std::cin >> a;
		std::cout << "Enter second integer:" << std::endl;
		std::cin >> b;
		if (b == 0){
			std::cout << "Error: division by zero" << std::endl;
			return 1;
			}
		da = a;
		std::cout << "Result: " << da / b << std::endl;
		// Hopefully this works first try
		std::cout << "After post-increment: " << a++ << std::endl;
		std::cout << "After pre-increment: " << ++a << std::endl;
		return 0;
	}
}
