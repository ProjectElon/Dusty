#pragma once

#include <SDL/SDL.h>

namespace dusty
{
	class Color
	{
	public:
		Color()
			: mR(0.0f)
			, mG(0.0f)
			, mB(0.0f)
			, mA(0.0f)
			, mPackedColor(0)
		{}

		explicit Color(
			const float &inR, 
			const float &inG, 
			const float &inB, 
			const float &inA)
			: mR(inR)
			, mG(inG)
			, mB(inB)
			, mA(inA)
		{
			Uint32 r = (Uint32)(mR * 255.0f);
			Uint32 g = (Uint32)(mG * 255.0f);
			Uint32 b = (Uint32)(mB * 255.0f);
			Uint32 a = (Uint32)(mA * 255.0f);
			mPackedColor = SDL_MapRGBA(mSurface->format, r, g, b, a);
		}

		inline const float& GetR() const
		{
			return mR;
		}

		inline const float& GetG() const
		{
			return mG;
		}

		inline const float& GetB() const
		{
			return mB;
		}

		inline const float& GetA() const
		{
			return mA;
		}

		inline const Uint32& ToInt() const
		{
			return mPackedColor;
		}

		static void SetSurface(SDL_Surface* surface)
		{
			mSurface = surface;
		}

	private:
		float mR;
		float mG;
		float mB;
		float mA;

		Uint32 mPackedColor;
		
		static SDL_Surface *mSurface;
	};
}