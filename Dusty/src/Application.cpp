#include "Window.h"
#include "Renderer.h"
#include "Vertex.h"
#include <vector>

int main(int argc, char* argv[])
{
	using namespace dusty;
	
	int result = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	
	if (result)
	{
		SDL_Log("Unable To Initialize SDL : %s", SDL_GetError());
		return -1;
	}

	Window window("Dusty", 800, 600);

	if (!window.Init())
	{
		SDL_Log("Unable To Open Window : %s", SDL_GetError());
		return -1;
	}

	Renderer context(&window);
	context.SetClearColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
	
	const Color White(1.0f, 1.0f, 1.0f, 0.0f);
	const Color Red(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Blue(0.0f, 0.0f, 1.0f, 1.0f);

	bool running = true;
	SDL_Event event;

	Uint64 previousTime = SDL_GetPerformanceCounter();
	const Uint64 frequency = SDL_GetPerformanceFrequency();
	
	int frames = 0;
	float timer = 0;

	std::vector< Vertex > vertices =
	{
		{ math::Vector3( -1, -1, -1) },
		{ math::Vector3(  1, -1, -1) },
		{ math::Vector3(  1,  1, -1) },
		{ math::Vector3( -1,  1, -1) },
		{ math::Vector3( -1, -1,  1) },
		{ math::Vector3(  1, -1,  1) },
		{ math::Vector3(  1,  1,  1) },
		{ math::Vector3( -1,  1,  1) }
	};

	std::vector< unsigned int > indices =
	{
		0, 1, 3, 
		3, 1, 2,
		1, 5, 2, 
		2, 5, 6,
		5, 4, 6, 
		6, 4, 7,
		4, 0, 7, 
		7, 0, 3,
		3, 2, 7, 
		7, 2, 6,
		4, 5, 0, 
		0, 5, 1
	};

	VertexList list(vertices, indices);

	float angle = 0.0f;

	while (running)
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		float deltaTime = (float)(currentTime - previousTime) / (float)frequency;
		previousTime = currentTime;

		++frames;
		timer += deltaTime;

		if (timer >= 1.0f)
		{
			timer -= 1.0f;
			printf("FPS : %d\n", frames);
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

		angle += deltaTime * 30.0f;
		if (angle > 360.0f) angle -= 360.0f;

		math::Matrix4 rotation    = math::RotationY(math::ToRadians(angle));
		math::Matrix4 scale		  = math::Scale(math::Vector3(500.0f, 500.0f, 1.0f));
		math::Matrix4 translation = math::Translation(math::Vector3(0.0f, 0.0f, 5.0f));

		context.Clear();

		context.DrawVertexList(list, Red, rotation * scale * translation);

		context.Update();
	}

	SDL_Quit();

	return 0;
}