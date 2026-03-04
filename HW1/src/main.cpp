#include <iostream>
#include "integer_utils.h"
#include "string_utils.h"
#include "grade_utils.h"
#include "while_count_utils.h"
#include "do_while_count_utils.h"

using std::cout;
using std::endl;
using std::cin;

int main(){
	int option;
	do{
		cout << "1. Integer operations" << endl;
		cout << "2. Character arrays and C-style strings" << endl;
		cout << "3. Grade evaluation" << endl;
		cout << "4. While-loop counting" << endl;
		cout << "5. Do-while and range-based for counting" << endl;
		cout << "6. Quit" << endl;
		cin >> option;
		if (cin.fail()){
			cin.clear();
			cin.ignore(500, '\n');
			option = -1;
		}
		switch(option){
			case 1:
				// Integer ops
				integer_utils::runIntegerOption();
			       	break;
			case 2:{
				// Characters and strings
				int result = string_utils::runStringOption();
				if (result == 1){
					return 1;
				}
				break;
			       }
			case 3: {
				// Grade eval
				int result = grade_utils::calculateGrade();
				if (result == 1){
					return 1;
				}
				break;
				}
			case 4:
				// While counting
				while_count_utils::runWhileCount();
				break;
			case 5:
				// Do while and range
				do_while_count_utils::runDoWhileCount();
				break;
			case 6:
				// Quit
				cout << "Goodbye!" << endl;
				break;
		}

	} while (option != 6);
	return 0;
}
