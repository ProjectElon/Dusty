#include "Window.h"
#include "Renderer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Loader.h"

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

	VertexList *list = Loader::GetInstance()->ReadObjFile("../res/cube.obj");
	Texture* brick = Loader::GetInstance()->LoadTexture("../res/brick.jpg");

	math::Vector3 p(0.0f, 0.0f, 5.0f);
	
	float speed = 50.0f;
	float yaw   = 0.0f;
	float pitch = 0.0f;

	// default Shaders
	VS vs;
	PS ps;
	ps.BindTexture(brick);

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

		if (keyState[SDL_SCANCODE_W])
		{
			p += math::Vector3(0.0f, 0.0f, 1.0f) * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_S])
		{
			p -= math::Vector3(0.0f, 0.0f, 1.0f) * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_UP])
		{
			pitch += deltaTime * speed;
		}

		if (keyState[SDL_SCANCODE_DOWN])
		{
			pitch -= deltaTime * speed;
		}

		if (keyState[SDL_SCANCODE_RIGHT])
		{
			yaw -= deltaTime * speed;
		}

		if (keyState[SDL_SCANCODE_LEFT])
		{
			yaw += deltaTime * speed;
		}

		vs.SetScale(math::Scale(math::Vector3(800.0f, 800.0f, 1.0f)));
		vs.SetRotation(math::RotationX(math::ToRadians(pitch)) * math::RotationY(math::ToRadians(yaw)));
		vs.SetTranslation(math::Translation(p));

		context.Begin();

		context.RenderVertexList(*list, &vs, &ps);
		
		context.End();
	}

	delete Loader::GetInstance();
	SDL_Quit();

	return 0;
}