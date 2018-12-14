#include "Window.h"

namespace dusty
{
	Window::Window(const std::string& title, const size_t& width, const size_t& height)
		: mTitle(title)
		, mWidth(width)
		, mHeight(height)
		, mHandle(nullptr)
	{}

	Window::~Window()
	{
		if (mHandle != nullptr)
		{
			SDL_DestroyWindow(mHandle);
		}
	}

	bool Window::Init()
	{
		const char* title = mTitle.c_str();

		mHandle = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			mWidth,
			mHeight,
			SDL_WINDOW_SHOWN
		);

		if (!mHandle)
		{
			return false;
		}

		return true;
	}
}