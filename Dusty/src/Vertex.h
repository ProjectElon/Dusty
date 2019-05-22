#pragma once

#include <vector>

#include "math/Math.h"

namespace dusty
{
	class Vertex
	{
	public:
		math::Vector3 position;
		math::Vector3 color;

		inline Vertex operator+(const Vertex& other) const
		{
			Vertex result;
			result.position = position + other.position;
			result.color = color + other.color;
			return result;
		}

		inline Vertex operator-(const Vertex& other) const
		{
			Vertex result;
			result.position = position - other.position;
			result.color = color - other.color;
			return result;
		}

		inline Vertex operator*(const float& scalar)
		{
			Vertex result;
			result.position = position * scalar;
			result.color = color * scalar;
			return result;
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