#include "Renderer.h"
#include "Window.h"

#include <cstring>

namespace dusty
{
	Renderer::Renderer(Window* window)
		: mWindow(window)
		, mScreen(SDL_GetWindowSurface(window->GetHandle()))
		, mPixels((Uint32*)(mScreen->pixels))
	{}

	Renderer::~Renderer() {}

	void Renderer::Clear() const
	{
		SDL_FillRect(mScreen, nullptr, mClearColor.ToInt(mScreen));
		SDL_LockSurface(mScreen);
	}

	void Renderer::DrawLine(float x0, float y0, float x1, float y1, const Color& color) const
	{
		float dx = x1 - x0;
		float dy = y1 - y0;
		
		if (dy == 0.0f && dx == 0.0f)
		{
			return;
		}

		if (abs(dy) > abs(dx))
		{
			if (dy < 0)
			{
				std::swap(x0, x1);
				std::swap(y0, y1);
				dy *= -1;
			}

			float nx = (x1 - x0) / dy;
			float ny = (y1 - y0) / dy;

			float x = x0;
			float y = y0;

			while (y <= y1)
			{
				int xd = (int)(x + 0.5f);
				int yd = (int)(y + 0.5f);

				x += nx;
				y += ny;

				if (xd < 0 || xd >= mWindow->GetWidth() ||
					yd < 0 || yd >= mWindow->GetHeight())
				{
					continue;
				}

				SetPixel(xd, yd, color);
			}
		}
		else
		{
			if (dx < 0)
			{
				std::swap(x0, x1);
				std::swap(y0, y1);
				dx *= -1;
			}

			float nx = (x1 - x0) / dx;
			float ny = (y1 - y0) / dx;

			float x = x0;
			float y = y0;

			while (x <= x1)
			{
				int xd = (int)(x + 0.5f);
				int yd = (int)(y + 0.5f);

				x += nx;
				y += ny;

				if (xd < 0 || xd >= mWindow->GetWidth() ||
					yd < 0 || yd >= mWindow->GetHeight())
				{
					continue;
				}
				
				SetPixel(xd, yd, color);
			}
		}
	}

	void Renderer::Update() const
	{
		SDL_UnlockSurface(mScreen);
		SDL_UpdateWindowSurface(mWindow->GetHandle());
	}
}