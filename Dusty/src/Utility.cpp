#include "Utility.h"

#include <sstream>

namespace dusty
{
	float ToFloat(const std::string& s)
	{
		return static_cast<float>(atof(s.c_str()));
	}

	int ToInt(const std::string& s)
	{
		return atoi(s.c_str());
	}

	std::vector< std::string > Split(const std::string& line, char delimiter)
	{
		std::vector< std::string > tokens;
		std::string token;

		std::istringstream iss(line);

		while (std::getline(iss, token, delimiter))
		{
			tokens.push_back(token);
		}

		return tokens;
	}
}