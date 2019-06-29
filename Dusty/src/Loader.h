#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "Utility.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace dusty
{
	class Loader
	{
	public:
		Loader() = default;
		~Loader();

		static Loader* GetInstance()
		{
			if (s_Instance == nullptr)
			{
				s_Instance = new Loader();
			}

			return s_Instance;
		}

		VertexList* ReadObjFile(const std::string& path);
		Texture* LoadTexture(const std::string& path);

	private:
		static Loader* s_Instance;

		std::unordered_map< std::string, VertexList* > m_Meshs;
		std::unordered_map< std::string, Texture* >    m_Textures;
	};
}