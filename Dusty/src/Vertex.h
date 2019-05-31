#pragma once

#include <vector>

#include "math/Math.h"

namespace dusty
{
	class Vertex
	{
	public:
		math::Vector3 position;
		math::Vector3 worldPos;

		math::Vector2 texCoord;
		math::Vector3 normal;

		Vertex(const math::Vector3& p, const math::Vector2& t, const math::Vector3& n)
			: position(p)
			, worldPos(p)
			, texCoord(t)
			, normal(n)
		{
		}

		inline Vertex operator+(const Vertex& other) const
		{
			return Vertex(
				position + other.position,
				texCoord + other.texCoord,
				normal   + other.normal
			);
		}

		inline Vertex operator-(const Vertex& other) const
		{
			return Vertex(
				position - other.position,
				texCoord - other.texCoord,
				normal   - other.normal
			);
		}

		inline Vertex operator*(const float& scalar)
		{
			return Vertex(
				position * scalar,
				texCoord * scalar,
				normal   * scalar
			);
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