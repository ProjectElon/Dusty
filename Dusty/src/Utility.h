#pragma once

#include <string>
#include <vector>
#include <stdio.h>

namespace dusty
{
	float ToFloat(const std::string& s);

	int ToInt(const std::string& s);
	
	std::vector< std::string > Split(const std::string& line, char delimiter = ' ');
}