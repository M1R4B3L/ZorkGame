#include "Utils.h"

bool Equals(std::string& str1, std::string& str2)
{
	return !(_strcmpi(str1.c_str(), str2.c_str()));
}

bool Equals(std::string& str1, const char* str2)
{
	return !(_strcmpi(str1.c_str(), str2));
}
