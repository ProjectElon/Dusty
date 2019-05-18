#pragma once

#include <string>
#include <SDL/SDL.h>

namespace dusty
{
	class Window
	{
	public:
		Window(const std::string& title, const size_t& width, const size_t& height);
		~Window();

		bool Init();
		
		inline SDL_Window*         GetHandle()  const { return mHandle; }
		inline const std::string&  GetTitle()  const { return mTitle;  }
		inline const size_t&       GetWidth()  const { return mWidth;  }
		inline const size_t&       GetHeight() const { return mHeight; }
		
		inline SDL_Surface* GetSurface() const
		{ 
			return SDL_GetWindowSurface(mHandle);
		}

	private:
		std::string mTitle;
		size_t      mWidth;
		size_t      mHeight;
		SDL_Window *mHandle;
	};
}