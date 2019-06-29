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

		virtual Vertex Execute(Vertex v) const = 0;

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

		void SetProjection(const math::Matrix4& projection)
		{
			m_Projection = projection;
		}

	protected:
		math::Matrix4 m_Scale;
		math::Matrix4 m_Rotation;
		math::Matrix4 m_Translation;
		math::Matrix4 m_Projection;
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

		Vertex Execute(Vertex v) const override
		{
			math::Matrix4 model = m_Scale * m_Rotation * m_Translation;

			v.worldPos = v.worldPos * model;
			v.position = math::Vector4(v.worldPos, 1.0f) * m_Projection;
			v.normal   = v.normal * m_Rotation;

			return v;
		}
	};
}