#include "Renderer.h"
#include "Window.h"

#include <cstring>

namespace dusty
{
	Renderer::Renderer(Window* window)
		: mWindow(window)
		, mScreen(SDL_GetWindowSurface(window->GetHandle()))
	{
		mPixels = (Uint32*)(mScreen->pixels);
	}

	Renderer::~Renderer() {}

	void Renderer::Clear() const
	{
		SDL_FillRect(mScreen, nullptr, mClearColor.ToInt(mScreen));
		SDL_LockSurface(mScreen);
	}

	void Renderer::Update() const
	{
		SDL_UnlockSurface(mScreen);
		SDL_UpdateWindowSurface(mWindow->GetHandle());
	}
}