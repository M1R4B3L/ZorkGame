#include "Globals.h"

bool Equals(std::string& a, std::string& b)
{
	return _strcmpi(a.c_str(), b.c_str()) == 0;
}

bool Equals(std::string& a, const char* b)
{
	return _strcmpi(a.c_str(), b) == 0;
}
