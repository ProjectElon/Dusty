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

	Window window("Dusty", 640, 480);

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

	VertexList* list = Loader::GetInstance()->ReadObjFile("../res/models/monkey.obj");
	Texture* texture = Loader::GetInstance()->LoadTexture("../res/textures/metal.jpg");

	math::Vector3 p(0.0f, 0.0f, 5.0f);
	
	float speed = 5.0f;
	float rotSpeed = 50.0f;
	float yaw = 180.0f;
	float pitch = 0.0f;

	// default Shaders
	VS vertexShader;
	PS pixelShader;
	pixelShader.BindTexture(texture);

	float fov = 100.0f;
	float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();
	vertexShader.SetProjection(math::Projection(math::ToRadians(fov), aspectRatio, 1.0f, 100.0f));
	vertexShader.SetScale(math::Scale(math::Vector3(2.0f, 2.0f, 2.0f)));

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
			p += math::Vector3::UnitZ * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_S])
		{
			p -= math::Vector3::UnitZ * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_A])
		{
			p -= math::Vector3::UnitX * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_D])
		{
			p += math::Vector3::UnitX * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_SPACE])
		{
			p += math::Vector3::UnitY * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_LSHIFT])
		{
			p -= math::Vector3::UnitY * speed * deltaTime;
		}

		if (keyState[SDL_SCANCODE_UP])
		{
			pitch += deltaTime * rotSpeed;
		}

		if (keyState[SDL_SCANCODE_DOWN])
		{
			pitch -= deltaTime * rotSpeed;
		}

		if (keyState[SDL_SCANCODE_RIGHT])
		{
			yaw -= deltaTime * rotSpeed;
		}

		if (keyState[SDL_SCANCODE_LEFT])
		{
			yaw += deltaTime * rotSpeed;
		}

		if (yaw > 360.0f)
		{
			yaw -= 360.0f;
		}

		if (yaw < 0.0)
		{
			yaw += 360.0f;
		}

		if (pitch > 360.0f) 
		{ 
			pitch -= 360.0f; 
		}

		if (pitch < 0.0)
		{ 
			pitch += 360.0f; 
		}

		vertexShader.SetRotation(math::RotationX(math::ToRadians(pitch)) * math::RotationY(math::ToRadians(yaw)));
		vertexShader.SetTranslation(math::Translation(p));

		context.Begin();
		context.RenderVertexList(*list, &vertexShader, &pixelShader);
		context.End();
	}

	SDL_Quit();

	delete Loader::GetInstance();

	return 0;
}