#include "Renderer.h"
#include "Window.h"
#include "Vertex.h"

namespace dusty
{
	Renderer::Renderer(Window* window)
		: m_Window(window)
		, m_Screen(window->GetSurface())
		, m_Pixels(reinterpret_cast<Uint32*>(m_Screen->pixels))
	{}

	Renderer::~Renderer() {}

	void Renderer::DrawLine(math::Vector2 v0, math::Vector2 v1, const math::Vector3& color) const
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

	void Renderer::DrawLine(const math::Vector3& v0, const math::Vector3& v1, const math::Vector3& color)
	{
		math::Vector2 p0 = TransformToScreenSpace(v0.PerspectiveDivide()).ToVector2();
		math::Vector2 p1 = TransformToScreenSpace(v1.PerspectiveDivide()).ToVector2();
		DrawLine(p0, p1, color);
	}

	void Renderer::RenderFlatBottomTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) 
	{
		float dy  = (v1.position.y - v0.position.y);
		float dx0 = (v1.position.x - v0.position.x) / dy;
		float dx1 = (v2.position.x - v0.position.x) / dy;

		int yStart = static_cast<int>(ceil(v0.position.y));
		int yEnd   = static_cast<int>(ceil(v1.position.y));

		float yPreStep = yStart - v0.position.y;
		float x0 = v0.position.x + yPreStep * dx0;
		float x1 = v0.position.x + yPreStep * dx1;

		for (int y = yStart; y < yEnd; ++y)
		{
			int xStart = static_cast< int >(ceil(x0));
			int xEnd   = static_cast< int >(ceil(x1));

			for (int x = xStart; x < xEnd; ++x)
			{
				float xp = x + 0.5f;
				float yp = y + 0.5f;

				float cls0 = yp - v0.position.y;

				Vertex p0 = math::Lerp(v0, v1, cls0 / dy);
				Vertex p1 = math::Lerp(v0, v2, cls0 / dy);

				float cls1 = xp - p0.position.x;
				float dx   = p1.position.x - p0.position.x;

				math::Vector3 color = math::Lerp(p0.color, p1.color, cls1 / dx);

				SetPixel(x, y, color);
			}

			x0 += dx0;
			x1 += dx1;
		}
	}
	
	void Renderer::RenderFlatTopTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
	{
		float dy  = (v0.position.y - v1.position.y);
		float dx0 = (v0.position.x - v1.position.x) / dy;
		float dx1 = (v0.position.x - v2.position.x) / dy;

		int yStart = static_cast<int>(ceil(v1.position.y));
		int yEnd   = static_cast<int>(ceil(v0.position.y));

		float yPreStep = yStart - v1.position.y;
		float x0 = v1.position.x + yPreStep * dx0;
		float x1 = v2.position.x + yPreStep * dx1;

		for (int y = yStart; y < yEnd; ++y)
		{
			int xStart = static_cast< int >(ceil(x0));
			int xEnd   = static_cast< int >(ceil(x1));

			for (int x = xStart; x < xEnd; ++x)
			{
				float xp = x + 0.5f;
				float yp = y + 0.5f;

				float cls0 = yp - v1.position.y;

				Vertex p0 = math::Lerp(v1, v0, cls0 / dy);
				Vertex p1 = math::Lerp(v2, v0, cls0 / dy);

				float cls1 = xp - p0.position.x;
				float dx   = p1.position.x - p0.position.x;

				math::Vector3 color = math::Lerp(p0.color, p1.color, cls1 / dx);

				SetPixel(x, y, color);
			}

			x0 += dx0;
			x1 += dx1;
		}
	}

	void Renderer::RenderTriangle(Vertex v0, Vertex v1, Vertex v2) 
	{
		if (v2.position.y < v1.position.y)
		{
			std::swap(v1, v2);
		}

		if (v1.position.y < v0.position.y)
		{
			std::swap(v0, v1);
		}

		if (v2.position.y < v1.position.y)
		{
			std::swap(v1, v2);
		}

		if (math::IsEqual(v1.position.y, v2.position.y))
		{
			if (v1.position.x > v2.position.x)
			{
				std::swap(v1, v2);
			}
		}

		if (math::IsEqual(v0.position.y, v1.position.y))
		{
			if (v0.position.x > v1.position.x)
			{
				std::swap(v0, v1);
			}
		}

		if (v0.position.y < v1.position.y && v0.position.y < v2.position.y && math::IsEqual(v1.position.y, v2.position.y))
		{
			RenderFlatBottomTriangle(v0, v1, v2);
		}
		else if (v2.position.y > v0.position.y && v2.position.y > v1.position.y && math::IsEqual(v0.position.y, v1.position.y))
		{
			RenderFlatTopTriangle(v2, v0, v1);
		}
		else
		{
			float cls = (v1.position.y - v0.position.y);
			float dis = (v2.position.y - v0.position.y);

			Vertex alphaSplit = math::Lerp(v0, v2, cls / dis);

			if (v1.position.x > alphaSplit.position.x)
			{
				std::swap(v1, alphaSplit);
			}

			RenderFlatBottomTriangle(v0, v1, alphaSplit);
			RenderFlatTopTriangle(v2, v1, alphaSplit);
		}
	}

	void Renderer::RenderVertexList(const VertexList& list, const math::Matrix4& mvp) 
	{
		const std::vector< Vertex >& vertices = list.GetVertices();
		const std::vector< unsigned int >& indices = list.GetIndices();

		for (unsigned int i = 0; i < indices.size(); i += 3)
		{
			Vertex v0 = vertices[indices[i + 0]];
			Vertex v1 = vertices[indices[i + 1]];
			Vertex v2 = vertices[indices[i + 2]];

			v0.position = v0.position * mvp;
			v1.position = v1.position * mvp;
			v2.position = v2.position * mvp;

			math::Vector3 normal = math::Vector3::Cross(v1.position - v0.position, v2.position - v0.position);

			float close = math::Vector3::Dot(v0.position, normal);

			if (close > 0.0f)
			{
				return;
			}

			v0.position = TransformToScreenSpace(v0.position.PerspectiveDivide());
			v1.position = TransformToScreenSpace(v1.position.PerspectiveDivide());
			v2.position = TransformToScreenSpace(v2.position.PerspectiveDivide());

			RenderTriangle(v0, v1, v2);
		}
	}

}