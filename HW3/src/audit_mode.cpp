#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "audit_mode.h"
#include "validation.h"

namespace audit_mode {
	void process_file(std::string input, std::string output){
		std::ifstream inFile(input);
		std::string fileType = input.substr(((input.size())-4), 4);
		std::ofstream outFile(output, std::ios::app);
		std::string outFileType = output.substr(((output.size())-4), 4);
		int extension = -1;
		if (fileType == ".tsv"){
			extension = 1;
		}
		if (fileType == ".csv"){
			extension = 0;
		}
		int outExtension = -1;
		if (outFileType == ".tsv"){
			outExtension = 1;
		}
		if (outFileType == ".csv"){
			outExtension = 0;
		}
		char delim, outDelim;
		if (extension){
			delim = '\t';
		}
		if (!extension){
			delim = ',';
		}
		if (outExtension){
			outDelim = '\t';
		}
		if (!outExtension){
			outDelim = ',';
		}
		std::string fileLine;
		if (inFile.is_open()){
			while(std::getline(inFile, fileLine)){
				std::istringstream line(fileLine);
				std::string username, email, password;
				std::getline(line, username, delim);
				std::getline(line, email, delim);
				std::getline(line, password);
				if (!validation::is_valid_password(password)){
						if (outFile.is_open()){
							outFile << username << outDelim << email << outDelim << password << std::endl;
						} else {
							std::cout << "Error opening file" << std::endl;
							return;
						}
					}
			}
		} else {
			std::cout << "Error opening file" << std::endl;
			return;
		}
	}
	void run_menu(){
		// stuff
	}
}
