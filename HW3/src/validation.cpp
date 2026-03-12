#include "validation.h"
#include <cctype>
#include <string>

namespace validation {
	bool is_valid_password(std::string password){
		// stuff
		if (password.size() < 8){
			return 0;
		}
		bool has_upper = 0;
		bool has_non_alnum = 0;
		for (const char& x : password){
			if (std::isupper(x)){
				has_upper = 1;
			}
			if (!std::isalnum(x)){
				has_non_alnum = 1;
			}
		}
		if (has_upper && has_non_alnum){
			return 1;
		} else {
			return 0;
		}
	}
}
