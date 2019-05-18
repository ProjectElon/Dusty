#pragma once

#include "Color.h"
#include "math/Math.h"
#include "Window.h"

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

		inline void Clear() const
		{
			SDL_FillRect(mScreen, nullptr, mClearColor.ToInt());
			SDL_LockSurface(mScreen);
		}

		inline void SetClearColor(const Color& color)
		{
			mClearColor = color;
		}

		inline void ToScreenSpace(math::Vector2& vector) const
		{
			vector.x = vector.x + (mWindow->GetWidth() / 2.0f);
			vector.y = (mWindow->GetHeight() / 2.0f) - vector.y;
		}

		inline math::Vector2 ApplyPerspective(const math::Vector3& vector)
		{
			math::Vector2 result;
			
			float invZ = 1.0f / vector.z;
			
			result.x = vector.x * invZ;
			result.y = vector.y * invZ;
			
			return result;
		}

		inline void SetPixel(const size_t &x, const size_t &y, const Color& color) const
		{
			
			if (x < 0 || x >= mWindow->GetWidth() || y < 0 || y >= mWindow->GetHeight())
			{
				return;
			}

			mPixels[mScreen->w * y + x] = color.ToInt();
		}
		
		inline void DrawLine(math::Vector2 v0, math::Vector2 v1, const Color& color) const;
		
		void DrawTriangle(
			const math::Vector2& v0,
			const math::Vector2& v1,
			const math::Vector2& v2,
			const Color& color) const;

		void DrawFlatBottomTriangle(
			const math::Vector2 &v0, 
			const math::Vector2 &v1, 
			const math::Vector2 &v2, 
			const Color& color) const;

		void DrawFlatTopTriangle(
			const math::Vector2 &v0,
			const math::Vector2 &v1, 
			const math::Vector2 &v2, 
			const Color& color) const;

		void DrawSolidTriangle(
			math::Vector2 v0, 
			math::Vector2 v1, 
			math::Vector2 v2, 
			const Color& color) const;
		
		void DrawVertexList(
			const VertexList& list, 
			const Color& color, 
			const math::Matrix4& mvp = math::Matrix4::Identity);

		void Update() const
		{
			SDL_UnlockSurface(mScreen);
			SDL_UpdateWindowSurface(mWindow->GetHandle());
		}
		
	private:
		class Window *mWindow;
		SDL_Surface  *mScreen;
		Color	      mClearColor;
		Uint32		 *mPixels;
	};
}