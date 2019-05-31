#pragma once

#include "math/Vector2.h"
#include "math/Vector3.h"

#include <string>
#include <algorithm>
#include <SDL/SDL.h>

namespace dusty
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		bool Load();

		inline const int& GetWidth()  const { return m_Source->w; }
		inline const int& GetHeight() const { return m_Source->h; }

		inline math::Vector3 GetTexel(const math::Vector2& coords)
		{
			int x = static_cast< int >(coords.x * (GetWidth() - 1) + 0.5f);
			int y = static_cast< int >(coords.y * (GetHeight() - 1) + 0.5f);

			// Texture wrapping
			x = std::max(0, std::min(x, GetWidth() - 1));
			y = std::max(0, std::min(y, GetHeight() - 1));

			Uint8 r, g, b;
			SDL_GetRGB(GetTexelLoc(x, y), m_Source->format, &r, &g, &b);
			float inv = 1.0f / 255.0f;
			return math::Vector3(r * inv, g * inv, b * inv);
		}

	private:
		std::string	 m_Path;
		SDL_Surface *m_Source;
		
		Uint32 GetTexelLoc(int x, int y)
		{
			// note: that i didn't write this code because SDL is a pain in the butt
			int bpp = m_Source->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to retrieve */
			Uint8* p = (Uint8*)m_Source->pixels + y * m_Source->pitch + x * bpp;

			switch (bpp)
			{
			case 1:
				return *p;
				break;

			case 2:
				return *(Uint16*)p;
				break;

			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;
				break;

			case 4:
				return *(Uint32*)p;
				break;

			default:
				return 0;       /* shouldn't happen, but avoids warnings */
			}

		}
	};
}