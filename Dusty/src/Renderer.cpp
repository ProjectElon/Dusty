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

	void Renderer::DrawLine(math::Vector2 v0, math::Vector2 v1, const Color& color) const
	{
		float dx = v1.x - v0.x;
		float dy = v1.y - v0.y;
		
		if (math::NearZero(dx) && math::NearZero(dy))
		{
			return;
		}

		if (abs(dy) > abs(dx))
		{
			if (dy < 0)
			{
				std::swap(v0, v1);
				dy *= -1;
			}

			math::Vector2 dv = (v1 - v0) / dy;

			for (math::Vector2 v = v0; v.y <= v1.y; v += dv)
			{
				int x = (int)ceil(v.x);
				int y = (int)ceil(v.y);

				if (x < 0 || x >= mWindow->GetWidth() ||
					y < 0 || y >= mWindow->GetHeight())
				{
					continue;
				}

				SetPixel(x, y, color);
			}
		}
		else
		{
			if (dx < 0)
			{
				std::swap(v0, v1);
				dx *= -1;
			}

			math::Vector2 dv = (v1 - v0) / dx;
			
			for (math::Vector2 v = v0; v.x <= v1.x; v += dv)
			{
				int x = (int)ceil(v.x);
				int y = (int)ceil(v.y);

				if (x < 0 || x >= mWindow->GetWidth() ||
					y < 0 || y >= mWindow->GetHeight())
				{
					continue;
				}
				
				SetPixel(x, y, color);
			}
		}
	}

	void Renderer::DrawTriangle(
		const math::Vector2& v0,
		const math::Vector2& v1,
		const math::Vector2& v2,
		const Color& color) const
	{
		DrawLine(v0, v1, color);
		DrawLine(v0, v2, color);
		DrawLine(v1, v2, color);
	}

	void Renderer::DrawSolidTriangle(
		math::Vector2 v0, 
		math::Vector2 v1, 
		math::Vector2 v2, 
		const Color& color) const
	{

		if (v2.y < v1.y)
		{
			std::swap(v1, v2);
		}

		if (v1.y < v0.y)
		{
			std::swap(v0, v1);
		}

		if (v2.y < v1.y)
		{
			std::swap(v1, v2);
		}

		if (v0.y < v1.y && v0.y < v2.y && math::IsEqual(v1.y, v2.y))
		{
			DrawFlatBottomTriangle(v0, v1, v2, color);
		}
		else if (v2.y > v0.y && v2.y > v1.y && math::IsEqual(v0.y, v1.y))
		{
			DrawFlatTopTriangle(v2, v1, v0, color);
		}
		else
		{
			float dvp = v1.y - v0.y;
			float dv  = v2.y - v0.y;
			math::Vector2 p = math::Lerp(v0, v2, dvp / dv);
			DrawFlatBottomTriangle(v0, v1, p, color);
			DrawFlatTopTriangle(v2, v1, p, color);
		}
	}

	void Renderer::DrawFlatBottomTriangle(
		math::Vector2 v0, 
		math::Vector2 v1, 
		math::Vector2 v2, 
		const Color& color) const
	{

		float dy0 = v1.y - v0.y;
		float dy1 = v2.y - v0.y;
		
		math::Vector2 dv0 = (v1 - v0) / dy0;
		math::Vector2 dv1 = (v2 - v0) / dy1;

		for (math::Vector2 va = v0, vb = v0; va.y <= v1.y; va += dv0, vb += dv1)
		{
			int minx = (int)ceil(va.x);
			int maxx = (int)ceil(vb.x);
			
			if (minx > maxx) std::swap(minx, maxx);

			int y = (int)ceil(va.y);

			if (y < 0 || y >= mWindow->GetHeight())
			{
				continue;
			}

			for (int x = minx; x < maxx; ++x)
			{
				if (x < 0 || x >= mWindow->GetWidth())
				{
					continue;
				}

				SetPixel(x, y, color);
			}

		}
	}

	void Renderer::DrawFlatTopTriangle(
		math::Vector2 v0, 
		math::Vector2 v1, 
		math::Vector2 v2, 
		const Color& color) const
	{
		float dy0 = v0.y - v1.y;
		float dy1 = v0.y - v2.y;

		math::Vector2 dv0 = (v1 - v0) / dy0;
		math::Vector2 dv1 = (v2 - v0) / dy1;

		for (math::Vector2 va = v0, vb = v0; va.y >= v1.y; va += dv0, vb += dv1)
		{
			int minx = (int)ceil(va.x);
			int maxx = (int)ceil(vb.x);
			
			if (minx > maxx)
			{
				std::swap(minx, maxx);
			}

			int y = (int)ceil(va.y);

			if (y < 0 || y >= mWindow->GetHeight())
			{
				continue;
			}

			for (int x = minx; x < maxx; ++x)
			{
				if (x < 0 || x >= mWindow->GetWidth())
				{
					continue;
				}

				SetPixel(x, y, color);
			}
		}
	}

	void Renderer::Update() const
	{
		SDL_UnlockSurface(mScreen);
		SDL_UpdateWindowSurface(mWindow->GetHandle());
	}
}