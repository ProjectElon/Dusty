#pragma once

#include <SDL/SDL.h>

namespace dusty
{
	class Color
	{
	public:
		float r;
		float g;
		float b;
		float a;

		Color()
			: r(0.0f)
			, g(0.0f)
			, b(0.0f)
			, a(0.0f)
		{}

		explicit Color(float inR, float inG, float inB, float inA)
			: r(inR)
			, g(inG)
			, b(inB)
			, a(inA)
		{}

		inline Uint32 ToInt(SDL_Surface *surface) const
		{
			Uint32 mr = (Uint32)(r * 255.0f);
			Uint32 mg = (Uint32)(g * 255.0f);
			Uint32 mb = (Uint32)(b * 255.0f);
			Uint32 ma = (Uint32)(a * 255.0f);
			return SDL_MapRGBA(surface->format, mr, mg, mb, ma);
		}

	};
}

namespace Colors
{
	static const dusty::Color White (1.0f, 1.0f, 1.0f, 1.0f);
	static const dusty::Color Black (0.0f, 0.0f, 0.0f, 1.0f);
	static const dusty::Color Red   (1.0f, 0.0f, 0.0f, 1.0f);
	static const dusty::Color Green (0.0f, 1.0f, 0.0f, 1.0f);
	static const dusty::Color Blue  (0.0f, 0.0f, 1.0f, 1.0f);
}