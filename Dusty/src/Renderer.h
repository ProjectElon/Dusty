#pragma once

#include "math/Math.h"
#include "Window.h"
#include "Texture.h"

#include <SDL/SDL.h>
#include <cstdio>

namespace dusty
{

	class Vertex;
	class VertexList;

	class Renderer
	{
	public:
		Renderer(Window* window);
		~Renderer();

		inline Uint32 GetIncodedColor(const math::Vector3& color) const
		{
			return SDL_MapRGBA(
				m_Screen->format, 
				(Uint8)(color.x * 255.0f), 
				(Uint8)(color.y * 255.0f), 
				(Uint8)(color.z * 255.0f), 
				255
			);
		}

		inline void Begin() const
		{
			SDL_FillRect(m_Screen, nullptr, GetIncodedColor(m_ClearColor));
			SDL_LockSurface(m_Screen);
		}

		inline void SetClearColor(const math::Vector3& color)
		{
			m_ClearColor = color;
		}

		inline math::Vector3 TransformToScreenSpace(const math::Vector3& vector) const
		{
			math::Vector3 result;

			result.x = vector.x + (m_Window->GetWidth() / 2.0f);
			result.y = (m_Window->GetHeight() / 2.0f) - vector.y;
			result.z = vector.z;

			return result;
		}

		inline void SetPixel(const size_t& x, const size_t& y, const math::Vector3& color) const
		{
			if (x < 0 || x >= m_Window->GetWidth() || y < 0 || y >= m_Window->GetHeight())
			{
				return;
			}

			m_Pixels[x + m_Screen->w * y] = GetIncodedColor(color);
		}
		
		inline void SetPixel(const size_t& x, const size_t& y, const unsigned int& color) const
		{
			if (x < 0 || x >= m_Window->GetWidth() || y < 0 || y >= m_Window->GetHeight())
			{
				return;
			}

			m_Pixels[x + m_Screen->w * y] = color;
		}

		void DrawLine(math::Vector2 v0, math::Vector2 v1, const math::Vector3& color) const;
		void DrawLine(const math::Vector3& v0, const math::Vector3& v1, const math::Vector3& color);
		
		void RenderFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Texture& texture);
		void RenderFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Texture& texture);
		void RenderTriangle(Vertex v0, Vertex v1, Vertex v2, const Texture& texture);
		void RenderVertexList(const VertexList& list, const Texture& texture, const math::Matrix4& mvp = math::Matrix4::Identity);

		inline void End() const
		{
			SDL_UnlockSurface(m_Screen);
			SDL_UpdateWindowSurface(m_Window->GetHandle());
		}
		
	private:
		class Window *m_Window;
		SDL_Surface  *m_Screen;
		math::Vector3 m_ClearColor;
		Uint32		 *m_Pixels;
	};
}