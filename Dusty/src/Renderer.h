#pragma once

#include "Color.h"

#include <SDL/SDL.h>

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
		
		void DrawLine(float x0, float y0, float x1, float y2, const Color& color) const;

		void Update() const;
		
	private:
		class Window *mWindow;
		SDL_Surface  *mScreen;
		Color	      mClearColor;
		Uint32		 *mPixels;
	};
}