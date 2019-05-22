#include "ZBuffer.h"

namespace dusty
{
	ZBuffer::ZBuffer(const unsigned int& width, const unsigned int& height)
		: m_Width(width)
		, m_Height(height)
	{
		m_Buffer = new float[width * height];
	}
	
	ZBuffer::~ZBuffer()
	{
		delete[] m_Buffer;
		m_Buffer = nullptr;
	}

	bool ZBuffer::test(int x, int y, float depth)
	{
		if (depth < GetDepth(x, y))
		{
			SetDepth(x, y, depth);
			return true;
		}

		return false;
	}
}