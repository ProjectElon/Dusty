#include "Renderer.h"
#include "Window.h"
#include "Vertex.h"

#include <iostream>

namespace dusty
{
	Renderer::Renderer(Window* window)
		: mWindow(window)
		, mScreen(window->GetSurface())
		, mPixels((Uint32*)(mScreen->pixels))
	{
		Color::SetSurface(window->GetSurface());
	}

	Renderer::~Renderer() {}

	void Renderer::DrawLine(math::Vector2 v0, math::Vector2 v1, const Color& color) const
	{
		bool steep = false;
		
		if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y))
		{
			std::swap(v0.x, v0.y);
			std::swap(v1.x, v1.y);
			steep = true;
		}

		if (v0.x > v1.x)
		{
			std::swap(v0, v1);
		}

		int dx = static_cast< int > (round(v1.x - v0.x));
		int dy = static_cast< int > (round(v1.y - v0.y));

		int error = 0;
		int y = v0.y;

		int maxX = round(v1.x);

		for (int x = round(v0.x); x <= maxX; ++x)
		{
			if (steep)
			{
				SetPixel(y, x, color);
			}
			else
			{
				SetPixel(x, y, color);
			}

			error += std::abs(dy) * 2;
			
			if (error > dx)
			{
				if (v1.y > v0.y)
				{
					y++;
				}
				else
				{
					--y;
				}

				error -= dx * 2;
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

	void Renderer::DrawFlatBottomTriangle(
		const math::Vector2& v0, 
		const math::Vector2& v1, 
		const math::Vector2& v2, 
		const Color& color) const
	{
		float dy  = (v1.y - v0.y);
		float dx0 = (v1.x - v0.x) / dy;
		float dx1 = (v2.x - v0.x) / dy;

		int maxY = static_cast<int>(ceil(v1.y));
		int currentY = static_cast<int>(ceil(v0.y));

		for (float x0 = v0.x, x1 = v0.x; currentY < maxY; currentY++, x0 += dx0, x1 += dx1)
		{
			int minX = static_cast< int >(ceil(x0));
			int maxX = static_cast< int >(ceil(x1));
			
			for (int x = minX; x <= maxX; ++x)
			{
				SetPixel(x, currentY, color);
			}
		}
	}

	void Renderer::DrawFlatTopTriangle(
		const math::Vector2 &v0, 
		const math::Vector2 &v1, 
		const math::Vector2 &v2, 
		const Color& color) const
	{
		float dy  = (v0.y - v1.y);
		float dx0 = (v0.x - v1.x) / dy;
		float dx1 = (v0.x - v2.x) / dy;
		
		int maxY = static_cast< int >(ceil(v0.y));
		int currentY = static_cast< int > (ceil(v1.y));

		for (float x0 = v1.x, x1 = v2.x; currentY < maxY; currentY++, x0 += dx0, x1 += dx1)
		{
			int minX = static_cast< int >(ceil(x0));
			int maxX = static_cast< int >(ceil(x1));
			
			for (int x = minX; x <= maxX; ++x)
			{
				SetPixel(x, currentY, color);
			}
		}
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

		if (math::IsEqual(v1.y, v2.y))
		{
			if (v1.x > v2.x)
			{
				std::swap(v1, v2);
			}
		}

		if (math::IsEqual(v0.y, v1.y))
		{
			if (v0.x > v1.x)
			{
				std::swap(v0, v1);
			}
		}

		if (v0.y < v1.y && v0.y < v2.y && math::IsEqual(v1.y, v2.y))
		{
			DrawFlatBottomTriangle(v0, v1, v2, color);
		}
		else if (v2.y > v0.y && v2.y > v1.y && math::IsEqual(v0.y, v1.y))
		{
			DrawFlatTopTriangle(v2, v0, v1, color);
		}
		else
		{
			float cls = (v1.y - v0.y);
			float dis = (v2.y - v0.y);
			
			math::Vector2 alphaSplit = math::Lerp(v0, v2, cls / dis);
			
			if (v1.x > alphaSplit.x)
			{
				std::swap(v1, alphaSplit);
			}

			DrawFlatBottomTriangle(v0, v1, alphaSplit, color);
			DrawFlatTopTriangle(v2, v1, alphaSplit, color);
		}
	}

	void Renderer::DrawVertexList(const VertexList& list, const Color& color, const math::Matrix4& mvp)
	{
		const std::vector< Vertex > &vertices = list.GetVertices();
		const std::vector< unsigned int > &indices = list.GetIndices();

		for (unsigned int i = 0; i < indices.size(); i += 3)
		{
			math::Vector3 p0 = vertices[ indices[i + 0] ].position;
			math::Vector3 p1 = vertices[ indices[i + 1] ].position;
			math::Vector3 p2 = vertices[ indices[i + 2] ].position;
			
			math::Vector2 v0 = ApplyPerspective(p0 * mvp);
			math::Vector2 v1 = ApplyPerspective(p1 * mvp);
			math::Vector2 v2 = ApplyPerspective(p2 * mvp);

			ToScreenSpace(v0);
			ToScreenSpace(v1);
			ToScreenSpace(v2);

			DrawSolidTriangle(v0, v1, v2, color);
		}
	}
}