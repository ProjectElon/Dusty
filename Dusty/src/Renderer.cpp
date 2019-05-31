#include "Renderer.h"
#include "Window.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <iostream>

namespace dusty
{
	Renderer::Renderer(Window* window)
		: m_Window(window)
		, m_Screen(window->GetSurface())
		, m_Pixels(reinterpret_cast< Uint32* >(m_Screen->pixels))
		, m_ZBuffer(new ZBuffer(window->GetWidth(), window->GetHeight()))
	{}

	Renderer::~Renderer()
	{
		delete m_ZBuffer;
		m_ZBuffer = nullptr;
	}

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
		int y = static_cast< int >(round(v0.y));

		int maxX = static_cast< int >(round(v1.x));

		for (int x = static_cast< int >(round(v0.x)); x <= maxX; ++x)
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

	void Renderer::RenderFlatBottomTriangle(
		const Vertex& v0, 
		const Vertex& v1, 
		const Vertex& v2, 
		PixelShader* ps)
	{
		float dy  = (v1.position.y - v0.position.y);
		float dx0 = (v1.position.x - v0.position.x) / dy;
		float dx1 = (v2.position.x - v0.position.x) / dy;

		int yStart = static_cast< int >(ceil(v0.position.y));
		int yEnd   = static_cast< int >(ceil(v1.position.y));

		float yPreStep = yStart - v0.position.y;
		float x0 = v0.position.x + yPreStep * dx0;
		float x1 = v0.position.x + yPreStep * dx1;

		for (int y = yStart; y < yEnd; ++y)
		{
			int xStart = static_cast< int >(ceil(x0));
			int xEnd   = static_cast< int >(ceil(x1));

			float alpha = ((y + 0.5f) - v0.position.y) / dy;
			Vertex p0 = math::Lerp(v0, v1, alpha);
			Vertex p1 = math::Lerp(v0, v2, alpha);

			for (int x = xStart; x < xEnd; ++x)
			{
				float dx   = p1.position.x - p0.position.x;
				float beta = ((x + 0.5f) - p0.position.x) / dx;
				Vertex p = math::Lerp(p0, p1, beta);

				float z = 1.0f / p.position.z;

				// depth testing
				if (!m_ZBuffer->test(x, y, z))
				{
					continue;
				}

				p *= z;

				p.normal.Normalize();

				SetPixel(x, y, ps->Execute(p));
			}

			x0 += dx0, x1 += dx1;
		}
	}
	
	void Renderer::RenderFlatTopTriangle(
		const Vertex& v0, 
		const Vertex& v1, 
		const Vertex& v2, 
		PixelShader* ps)
	{
		float dy  = (v0.position.y - v1.position.y);
		float dx0 = (v0.position.x - v1.position.x) / dy;
		float dx1 = (v0.position.x - v2.position.x) / dy;

		int yStart = static_cast< int >(ceil(v1.position.y));
		int yEnd   = static_cast< int >(ceil(v0.position.y));

		float yPreStep = yStart - v1.position.y;
		float x0 = v1.position.x + yPreStep * dx0;
		float x1 = v2.position.x + yPreStep * dx1;
		
		for (int y = yStart; y < yEnd; ++y)
		{
			int xStart = static_cast< int >(ceil(x0));
			int xEnd   = static_cast< int >(ceil(x1));

			float alpha = ((y + 0.5f) - v1.position.y) / dy;

			Vertex p0 = math::Lerp(v1, v0, alpha);
			Vertex p1 = math::Lerp(v2, v0, alpha);

			for (int x = xStart; x < xEnd; ++x)
			{
				float dx   = p1.position.x - p0.position.x;
				float beta = ((x + 0.5f) - p0.position.x) / dx;

				Vertex p = math::Lerp(p0, p1, beta);
				
				float z = 1.0f / p.position.z;
				
				// depth testing
				if (!m_ZBuffer->test(x, y, z))
				{
					continue;
				}
				
				p *= z;

				SetPixel(x, y, ps->Execute(p));
			}

			x0 += dx0, x1 += dx1;
		}
	}

	void Renderer::RenderTriangle(Vertex v0, Vertex v1, Vertex v2, PixelShader* ps)
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
			RenderFlatBottomTriangle(v0, v1, v2, ps);
		}
		else if (v2.position.y > v0.position.y && v2.position.y > v1.position.y && math::IsEqual(v0.position.y, v1.position.y))
		{
			RenderFlatTopTriangle(v2, v0, v1, ps);
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

			RenderFlatBottomTriangle(v0, v1, alphaSplit, ps);
			RenderFlatTopTriangle(v2, v1, alphaSplit, ps);
		}
	}

	void Renderer::RenderVertexList(const VertexList& list, VertexShader* vs, PixelShader* ps)
	{
		const std::vector< Vertex >& vertices = list.GetVertices();
		const std::vector< unsigned int >& indices = list.GetIndices();

		for (unsigned int i = 0; i < indices.size(); i += 3)
		{
			Vertex v0 = vs->Execute( vertices[indices[i + 0]] );
			Vertex v1 = vs->Execute( vertices[indices[i + 1]] );
			Vertex v2 = vs->Execute( vertices[indices[i + 2]] );

			math::Vector3 normal = math::Vector3::Cross(v1.position - v0.position, v2.position - v0.position);
			math::Vector3 eye = math::Vector3::Zero;

			// back face culling
			if (math::Vector3::Dot(v0.position - eye, normal) >= 0.0f)
			{
				continue;
			}

			TransformToSceenSpace(v0);
			TransformToSceenSpace(v1);
			TransformToSceenSpace(v2);

			RenderTriangle(v0, v1, v2, ps);
		}
	}

}