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
	context.SetClearColor(math::Vector3(0.0f, 0.0f, 0.0f));
	
	bool running = true;
	SDL_Event event;

	Uint64 previousTime = SDL_GetPerformanceCounter();
	const Uint64 frequency = SDL_GetPerformanceFrequency();
	
	int frames = 0;
	float timer = 0;

	std::vector< Vertex > vertices =
	{
		{ math::Vector3( 0.0f,  0.5f, 1.0f), math::Vector2(0.5f, 0.0f) },
		{ math::Vector3(-0.5f, -0.5f, 1.0f), math::Vector2(0.0f, 1.0f) },
		{ math::Vector3( 0.5f, -0.5f, 1.0f), math::Vector2(1.0f, 1.0f) }
	};

	std::vector< unsigned int > indices =
	{
		0, 1, 2
	};

	VertexList list(vertices, indices);

	math::Vector3 p0(0.0f, 0.0f, 10.0f), p1(0.0f, 0.0f, 20.0f);
	math::Matrix4 rot0 = math::RotationZ(math::Pi / 2.0f);
	math::Matrix4 rot1 = math::RotationZ(-math::Pi / 2.0f);

	float speed = 50.0f;

	Texture brick("../res/brick.jpg"), container("../res/container.jpg");

	if (!brick.Load())
	{
		return -1;
	}

	if (!container.Load())
	{
		return -1;
	}

	while (running)
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();
		float deltaTime = static_cast< float >((double)(currentTime - previousTime) / (double)frequency);
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

		if (keyState[SDL_SCANCODE_UP])
		{
			p0 += math::Vector3(0.0f, 0.0f, 1.0f) * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_DOWN])
		{
			p0 -= math::Vector3(0.0f, 0.0f, 1.0f) * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_W])
		{
			p1 += math::Vector3(0.0f, 0.0f, 1.0f) * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_S])
		{
			p1 -= math::Vector3(0.0f, 0.0f, 1.0f) * speed * deltaTime;
		}
		
		math::Matrix4 scale		  = math::Scale(math::Vector3(1000.0f, 1000.0f, 1.0f));
		math::Matrix4 translation0 = math::Translation(p0);
		math::Matrix4 translation1 = math::Translation(p1);

		context.Begin();

		context.RenderVertexList(list, brick, rot0 * scale * translation0);
		context.RenderVertexList(list, container, rot1 * scale * translation1);

		context.End();
	}

	SDL_Quit();

	return 0;
}