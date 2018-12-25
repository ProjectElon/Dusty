#include "Window.h"
#include "Renderer.h"

#include <iostream>
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(nullptr));

	using namespace dusty;
	
	int result = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	
	if (result)
	{
		SDL_Log("Unable To Initialize SDL : %s", SDL_GetError());
		return -1;
	}

	Window window("Dusty", 640, 480);

	if (!window.Init())
	{
		SDL_Log("Unable To Open Window : %s", SDL_GetError());
		return -1;
	}

	Renderer context(&window);
	context.SetClearColor(Colors::Black);

	bool running = true;
	SDL_Event event;

	Uint64 previousTime    = SDL_GetPerformanceCounter();
	const Uint64 frequency = SDL_GetPerformanceFrequency();
	
	int frames = 0;
	double timer = 0;


	float r = (float)rand() / (float)RAND_MAX;
	float g = (float)rand() / (float)RAND_MAX;
	float b = (float)rand() / (float)RAND_MAX;
	float a = (float)rand() / (float)RAND_MAX;


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

			r = (float)rand() / (float)RAND_MAX;
			g = (float)rand() / (float)RAND_MAX;
			b = (float)rand() / (float)RAND_MAX;
			a = (float)rand() / (float)RAND_MAX;

			frames = 0;
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					running = false;
					break;
				}
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(nullptr);
		
		if (keyState[SDL_SCANCODE_ESCAPE])
		{
			running = false;
		}

		context.Clear();

		float w = window.GetWidth();
		float h = window.GetHeight();

		math::Vector2 v0(w / 2, 0.0f);
		math::Vector2 v1(0, h);
		math::Vector2 v2(w, h);

		Color color(r, g, b, a);

		context.DrawSolidTriangle(v0, v1, v2, color);

		context.Update();
	}

	SDL_Quit();

	return 0;
}