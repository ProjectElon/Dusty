#pragma once

#include "Color.h"
#include "math/Vector2.h"

#include <SDL/SDL.h>
#include <iostream>

namespace dusty
{
	class Renderer
	{
	public:
		Renderer(class Window* window);
		~Renderer();

		void Clear() const;

		inline void SetClearColor(const Color& color)
		{
			mClearColor = color;
		}

		inline void SetPixel(const size_t &x, const size_t &y, const Color& color) const
		{
			mPixels[mScreen->w * y + x] = color.ToInt(mScreen);
		}
		
		inline void DrawLine(math::Vector2 v0, math::Vector2 v1, const Color& color) const;
		
		void DrawTriangle(
			const math::Vector2 &v0,
			const math::Vector2& v1,
			const math::Vector2& v2,
			const Color& color) const;

		void DrawSolidTriangle(
			math::Vector2 v0, 
			math::Vector2 v1, 
			math::Vector2 v2, 
			const Color& color) const;

		void DrawFlatBottomTriangle(
			math::Vector2 v0, 
			math::Vector2 v1, 
			math::Vector2 v2, 
			const Color& color) const;

		void DrawFlatTopTriangle(
			math::Vector2 v0,
			math::Vector2 v1, 
			math::Vector2 v2, 
			const Color& color) const;

		void Update() const;
		
	private:
		class Window *mWindow;
		SDL_Surface  *mScreen;
		Color	      mClearColor;
		Uint32		 *mPixels;
	};
}