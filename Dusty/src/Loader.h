#pragma once

#include "Vertex.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace dusty
{
	class Loader
	{
	public:
		Loader();
		~Loader();

		VertexList* ReadObjFile(const std::string& path);

	private:
		std::vector< std::string > Split(const std::string& line, char delimiter = ' ') const;
		
		inline float ToFloat(const std::string& s) const
		{
			return static_cast<float>(atof(s.c_str()));
		}

		inline int ToInt(const std::string& s) const
		{
			return atoi(s.c_str());
		}

		std::unordered_map< std::string, VertexList* > m_Meshs;
	};
}