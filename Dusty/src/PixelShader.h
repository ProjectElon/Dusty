#pragma once

#include "Vertex.h"
#include "Texture.h"

namespace dusty
{
	class PixelShader
	{
	public:
		PixelShader() = default;

		virtual ~PixelShader()
		{
		}

		virtual math::Vector3 Execute(const Vertex& vertex) = 0;
		
		inline void BindTexture(Texture* texture)
		{
			m_Textures.push_back(texture);
		}

		inline Texture* GetTexture(int slot)
		{
			return m_Textures[slot];
		}

	private:
		std::vector< Texture* > m_Textures;
	};

	class PS : public PixelShader
	{
	public:
		~PS()
		{
		}

		/*
			(important note) :
			* the givin vertex data corresponds to the pixel data itself 
			* you can use the world position and the normal to do any calculations
		*/
		math::Vector3 Execute(const Vertex& vertex) override
		{
			math::Vector3 base = GetTexture(0)->GetTexel(vertex.texCoord);
			math::Vector3 ambient = base * 0.1f;
			float intensity = std::max(-math::Vector3::Dot(lightDir, vertex.normal), 0.0f);
			math::Vector3 diffuse = math::Vector3::Hadamard(base, lightColor) * intensity;
			return ambient + diffuse;
		}

	private:
		math::Vector3 lightDir = math::Vector3(0.0f, 0.0f, 1.0f);
		math::Vector3 lightColor = math::Vector3(1.0f, 1.0f, 1.0f);
	};
}