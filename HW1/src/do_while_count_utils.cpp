#include <iostream>
#include "do_while_count_utils.h"

namespace do_while_count_utils{
	int runDoWhileCount(){
		int uin;
		do{
			std::cout << "Enter a number between 1 and 5:" << std::endl;
			std::cin >> uin;
		} while (uin < 1 || uin > 5);
		int arry[] = {1, 2, 3, 4, 5};
		for (int x : arry){
			std::cout << "Value: " << x << std::endl;
			if (x == uin){
				return 0;
			}
		}
	}
}
