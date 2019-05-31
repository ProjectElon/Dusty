#pragma once

#include "Vertex.h"

namespace dusty
{
	class VertexShader
	{
	public:
		VertexShader() = default;

		virtual ~VertexShader()
		{
		}

		virtual Vertex Execute(const Vertex& vertex) = 0;

		void SetScale(const math::Matrix4& scale)
		{
			m_Scale = scale;
		}

		void SetRotation(const math::Matrix4& rotation)
		{
			m_Rotation = rotation;
		}

		void SetTranslation(const math::Matrix4& translation)
		{
			m_Translation = translation;
		}

	protected:
		math::Matrix4 m_Scale;
		math::Matrix4 m_Rotation;
		math::Matrix4 m_Translation;
	};

	class VS : public VertexShader
	{
	public:
		VS()
		{
		}

		~VS()
		{
		}

		Vertex Execute(const Vertex& vertex) override
		{
			Vertex v = vertex;
			
			v.position = v.position * m_Rotation * m_Scale * m_Translation;
			v.worldPos = v.position;
			v.normal   = v.normal * m_Rotation;

			return v;
		}
	};
}