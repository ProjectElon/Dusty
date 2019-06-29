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
		
		inline SDL_Window*         GetHandle() const { return m_Handle; }
		inline const std::string&  GetTitle()  const { return m_Title;  }
		inline const size_t&       GetWidth()  const { return m_Width;  }
		inline const size_t&       GetHeight() const { return m_Height; }
		
		inline SDL_Surface* GetSurface() const
		{ 
			return SDL_GetWindowSurface(m_Handle);
		}

	private:
		std::string m_Title;
		size_t      m_Width;
		size_t      m_Height;
		SDL_Window *m_Handle;
	};
}