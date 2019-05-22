#pragma once

#include "math/Vector3.h"

#include <string>
#include <SDL/SDL.h>

namespace dusty
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		bool Load();

		const unsigned int& GetWidth()  const { return m_Source->w; }
		const unsigned int& GetHeight() const { return m_Source->h; }

		inline math::Vector3 GetTexel(int x, int y) const
		{
			Uint8 r, g, b;
			SDL_GetRGB(GetTexelLoc(x, y), m_Source->format, &r, &g, &b);
			float inv = 1.0f / 255.0f;
			return math::Vector3(r * inv, g * inv, b * inv);
		}

	private:
		std::string	 m_Path;
		SDL_Surface *m_Source;
		
		inline Uint32 GetTexelLoc(const int& x, const int& y) const
		{
			// note: that i didn't write this code because SDL is a pain in the butt

			int bpp = m_Source->format->BytesPerPixel;
			
			Uint8* p = (Uint8*)m_Source->pixels + y * m_Source->pitch + x * bpp;

			switch (bpp)
			{
			case 1:
				return *p;

			case 2:
				return *(Uint16*)p;

			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;

			case 4:
				return *(Uint32*)p;

			default:
				return 0;
			}
		}
	};
}