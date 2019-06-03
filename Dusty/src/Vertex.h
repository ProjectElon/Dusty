#pragma once

#include <vector>

#include "math/Math.h"

namespace dusty
{
	class Vertex
	{
	public:
		math::Vector4 position;
		math::Vector3 worldPos;
		math::Vector2 texCoord;
		math::Vector3 normal;

		Vertex()
		{}

		Vertex(const Vertex& other)
		{
			position = other.position;
			worldPos = other.worldPos;
			texCoord = other.texCoord;
			normal   = other.normal;
		}

		Vertex& operator=(const Vertex& other)
		{
			position = other.position;
			worldPos = other.worldPos;
			texCoord = other.texCoord;
			normal   = other.normal;
			return *this;
		}

		inline Vertex operator+(const Vertex& other) const
		{
			Vertex result;

			result.position = position + other.position;
			result.worldPos = worldPos + other.worldPos;
			result.texCoord = texCoord + other.texCoord;
			result.normal   = normal   + other.normal;

			return result;
		}

		inline Vertex operator-(const Vertex& other) const
		{
			Vertex result;

			result.position = position - other.position;
			result.worldPos = worldPos - other.worldPos;
			result.texCoord = texCoord - other.texCoord;
			result.normal   = normal   - other.normal;

			return result;
		}

		inline Vertex operator*(const float& scalar)
		{
			Vertex result;

			result.position = position * scalar;
			result.worldPos = worldPos * scalar;
			result.texCoord = texCoord * scalar;
			result.normal   = normal   * scalar;

			return result;
		}

		inline Vertex& operator*=(const float& scalar)
		{
			position *= scalar;
			worldPos *= scalar;
			texCoord *= scalar;
			normal   *= scalar;
			return *this;
		}
	};

	class VertexList
	{
	private:
		std::vector< Vertex > m_Vertices;
		std::vector< unsigned int > m_Indices;

	public:
		VertexList(
			const std::vector<Vertex>& vertices, 
			const std::vector<unsigned int>& indices)
			: m_Vertices(vertices)
			, m_Indices(indices)
		{
			assert(indices.size() % 3 == 0);
		}

		inline const std::vector<Vertex>& GetVertices() const
		{
			return m_Vertices;
		}

		inline const std::vector<unsigned int>& GetIndices() const
		{
			return m_Indices;
		}
	};
}