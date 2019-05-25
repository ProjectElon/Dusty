#include "Loader.h"
#include "math/Math.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

namespace dusty
{
	Loader::Loader()
	{
	}

	Loader::~Loader()
	{
		for (auto mesh : m_Meshs)
		{
			delete mesh.second;
		}
	}

	VertexList* Loader::ReadObjFile(const std::string& path)
	{
		auto it = m_Meshs.find(path);

		if (it != m_Meshs.end())
		{
			return it->second;
		}

		std::ifstream ifs(path);
		
		if (!ifs.is_open())
		{
			std::cout << "Unable To Read File : " << path << std::endl;
			return nullptr;
		}

		std::vector< math::Vector3 > positions;
		std::vector< math::Vector2 > texCoords;
		std::vector< math::Vector3 > normals;

		std::vector< Vertex > vertices;
		std::vector< unsigned int > indices;

		std::map< std::tuple< int, int, int >, int > index;

		std::string currentLine;

		while (std::getline(ifs, currentLine))
		{
			auto tokens = Split(currentLine);
			
			if (!tokens.size()) continue;

			std::string mark = tokens[0];

			if (mark == "v")
			{
				math::Vector3 p(
					ToFloat(tokens[1]),
					ToFloat(tokens[2]),
					ToFloat(tokens[3])
				);
				positions.push_back(p);
			}
			else if (mark == "vt")
			{
				math::Vector2 t(
					ToFloat(tokens[1]),
					ToFloat(tokens[2])
				);
				texCoords.push_back(t);
			}
			else if (mark == "vn")
			{
				math::Vector3 n(
					ToFloat(tokens[1]),
					ToFloat(tokens[2]),
					ToFloat(tokens[3])
				);
				normals.push_back(n);
			}
			else if (mark == "f")
			{
				for (int i = 1; i < 4; i++)
				{
					auto vertex = Split(tokens[i], '/');

					int p = ToInt(vertex[0]) - 1;
					int t = ToInt(vertex[1]) - 1;
					int n = ToInt(vertex[2]) - 1;

					auto target = std::make_tuple<>(p, t, n);
					auto it = index.find(target);
					
					if (it == index.end())
					{
						Vertex vertex;
						
						vertex.position = positions[p];
						vertex.texCoord = texCoords[t];
						vertex.normal   = normals[n];

						vertices.push_back(vertex);
						indices.push_back(vertices.size() - 1);
						index.emplace(target, vertices.size() - 1);
					}
					else
					{
						indices.push_back(it->second);
					}
				}
			}
		}

		VertexList* list = new VertexList(vertices, indices);
		m_Meshs.emplace(path, list);

		ifs.close();

		return list;
	}


	std::vector< std::string > Loader::Split(const std::string& line, char delimiter) const
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