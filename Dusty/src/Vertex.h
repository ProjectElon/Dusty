#pragma once

#include <vector>

#include "math/Math.h"

namespace dusty
{
	class Vertex
	{
	public:
		math::Vector3 position;
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