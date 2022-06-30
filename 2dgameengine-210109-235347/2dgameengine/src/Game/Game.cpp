#include "Game.h"

// Global Variables
glm::vec2 playerPos;
glm::vec2 playerVeloc;

Game::Game()
{
	isRunning = false;
	registry = std::make_unique<Registry>();
	Logger::Log("Game Constructor Called");
}

Game:: ~Game()
{
	Logger::Log("Game Destructor Called");
}

void	Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Err("Error initializing SDL");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800;
	windowHeight = 600;

	window = SDL_CreateWindow(
		"Engine",
		 SDL_WINDOWPOS_CENTERED,
		 SDL_WINDOWPOS_CENTERED,
		 windowWidth,
		 windowHeight,
		 SDL_WINDOW_BORDERLESS
	);
	if (!window)
	{
		Logger::Err("Error creating SDL Window");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		Logger::Err("Error creating SDL Renderer");
		return;
	}
	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}

void	Game::Run()
{
	Setup();
	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void	Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while(SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					isRunning = false;
				break;
			default:
				break;
		}
	}
}

void	Game::Setup()
{
	Entity tank = registry->CreateEntity();

	registry->AddComponent<TransformComponent>(tank, glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 0.0);
	registry->AddComponent<RigidBodyComponent>(tank, glm::vec2(50.0, 0.0));

}

void	Game::Update()
{
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
		SDL_Delay(timeToWait);

	double deltaT = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

	// stores the "previous" frame time (ticks after the SDL_Delay)
	millisecsPreviousFrame = SDL_GetTicks();

	playerPos.x += playerVeloc.x * deltaT;
	playerPos.y += playerVeloc.y * deltaT;
}

void	Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);
	// SDL_Surface *surface = IMG_Load("../assets/images/tank-tiger-right.png");
	// SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	// SDL_FreeSurface(surface);
	// SDL_Rect destRect = {static_cast<int>(playerPos.x), static_cast<int>(playerPos.y), 32, 32};
	// SDL_RenderCopy(renderer, texture, NULL, &destRect);
	// SDL_DestroyTexture(texture);
	SDL_RenderPresent(renderer);
}

void	Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
