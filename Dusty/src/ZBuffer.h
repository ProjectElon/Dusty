#pragma once

#include <limits>

namespace dusty
{
	class ZBuffer
	{
	public:
		ZBuffer(const unsigned int& width, const unsigned int& height);
		~ZBuffer();

		bool Test(int x, int y, float depth);

		inline void Clear()
		{
			unsigned int size = m_Width * m_Height;
			
			for (unsigned int i = 0; i < size; i++)
			{
				m_Buffer[i] = std::numeric_limits< float >::infinity();
			}
		}

		inline void SetDepth(int x, int y, float depth)
		{
			m_Buffer[x + y * m_Width] = depth;
		}

		inline float GetDepth(int x, int y) const
		{
			return m_Buffer[x + y * m_Width];
		}

		const unsigned int& GetWidth()  const { return m_Width; }
		const unsigned int& GetHeight() const { return m_Height; }

	private:
		float*       m_Buffer;
		unsigned int m_Width;
		unsigned int m_Height;
	};
}