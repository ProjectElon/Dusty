#include "Window.h"
#include "Renderer.h"

#include <iostream>
#include <ctime>

int main(int argc, char* argv[])
{
	int result = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	
	if (result)
	{
		SDL_Log("Unable To Initialize SDL : %s", SDL_GetError());
		return -1;
	}

	dusty::Window window("Dusty", 800, 600);

	if (!window.Init())
	{
		SDL_Log("Unable To Open Window : %s", SDL_GetError());
		return -1;
	}

	dusty::Renderer renderer(&window);
	renderer.SetClearColor(dusty::Color(0.0f, 0.0f, 0.0f, 1.0f));

	bool running = true;
	SDL_Event event;

	Uint64 previousTime    = SDL_GetPerformanceCounter();
	const Uint64 frequency = SDL_GetPerformanceFrequency();
	
	int frames = 0;
	double timer = 0;

	while (running)
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		double deltaTime = (double)(currentTime - previousTime) / (double)frequency;
		previousTime = currentTime;

		++frames;
		timer += deltaTime;

		if (timer >= 1.0)
		{
			timer -= 1.0;
			std::cout << "Fps : " << frames << std::endl;
			frames = 0;
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					running = false;
				} break;
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(nullptr);
		
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			running = false;
		}

		renderer.Clear();
		renderer.Update();
	}

	SDL_Quit();

	return 0;
}