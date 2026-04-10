#include <iostream>
#include <cstring>   // for strlen, strcpy
#include <stdexcept>

// TODO: function prototypes

// TODO: implement addStudent
void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity){
	if (size == capacity)
		throw std::runtime_error("List full");
	names[size] = name;
	gpas[size] = gpa;
	size++;
	return;
}
// TODO: implement updateGPA
void updateGPA(double* gpaPtr, double newGpa){
	*gpaPtr = newGpa;
	return;
}
// TODO: implement printStudent
void printStudent(const char* name, const double& gpa){
	std::cout << name << ' ' << gpa << std::endl;
	return;
}
// TODO: implement averageGPA
double averageGPA(const double gpas[], int size){
	if (size == 0)
		throw std::runtime_error("No students");
	double sum;
	for (int i = 0; i < size; i++){
		sum += gpas[i];
	}
	double average = (sum / size);
	return average;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <capacity>" << std::endl;
        return 1;
    }

    // VLAs, not covered
    //char* names[capacity];
    //double gpas[capacity];
    int capacity = std::stoi(argv[1]);

    char** names = new char*[capacity];
    double* gpas = new double[capacity];
    int size = 0;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
	case 1: {
		// TODO: implement menu logic
		std::string inpName;
		double gpa;
		std::cout << "Student Name?" << std::endl;
		std::cin >> inpName;
		std::cout << "Student GPA?" << std::endl;
		std::cin >> gpa;
		char* name = inpName.data();
		// Implement exceptions
		try {
			addStudent(name, gpa, names, gpas, size, capacity);
		} catch (const std::runtime_error& e) {
			std::cout << e.what() << std::endl;
		}
                break;
            }
            case 2: {
                // TODO: implement menu logic
		int index;
		std::cin >> index;
		double newGpa;
		std::cin >> newGpa;
		updateGPA(&gpas[index], newGpa);
                break;
            }
            case 3: {
                // TODO: implement menu logic
		for (int i = 0; i < size; i++){
			printStudent(names[i], gpas[i]);
		}
                break;
            }
            case 4: {
                // TODO: implement menu logic
		// Implement exception
		double avg;
		try {
			avg = averageGPA(gpas, size);
			std::cout << "Average GPA " << avg << std::endl;
		} catch (const std::runtime_error& e) {
			std::cout << e.what() << std::endl;
		}
                break;
            }
            case 5: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    } while (choice != 5);

    // TODO: free memory
	for (int i = 0; i < size; i++){
		delete[] names[i];
	}
    	delete[] names;
	delete[] gpas;
    return 0;
}
