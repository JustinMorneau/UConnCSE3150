#include <iostream>
#include "grade_utils.h"

namespace grade_utils {
double calculateGrade(){
	std::cout << "Enter student type (U for undergrad, G for grad):" << std::endl;
	char type;
	double grade;
	std::cin >> type;
	std::cout << "Enter numeric grade:" << std::endl;
	std::cin.ignore();
	std::cin >> grade;
	if (grade < 0 || grade > 100){
		std::cout << "Invalid grade" << std::endl;
		return 1;
	}
	if (((type == 'U' || type == 'u') && grade >= 60) || ((type == 'G' || type == 'g') && grade >= 70)){
		std::cout << "Status: Pass" << std::endl;
	} else {
		std::cout << "Status: Fail" << std::endl;
	}
	return grade;
}	
}
