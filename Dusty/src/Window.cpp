#include "Window.h"

namespace dusty
{
	Window::Window(const std::string& title, const size_t& width, const size_t& height)
		: m_Title(title)
		, m_Width(width)
		, m_Height(height)
		, m_Handle(nullptr)
	{}

	Window::~Window()
	{
		if (m_Handle != nullptr)
		{
			SDL_DestroyWindow(m_Handle);
		}
	}

	bool Window::Init()
	{
		const char* title = m_Title.c_str();

		m_Handle = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_Width,
			m_Height,
			SDL_WINDOW_SHOWN
		);

		if (!m_Handle)
		{
			return false;
		}

		return true;
	}
}