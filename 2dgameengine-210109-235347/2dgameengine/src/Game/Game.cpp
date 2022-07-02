#include "Game.h"

Game::Game()
{
	isRunning = false;
	registry = std::make_unique<Registry>();
	assetManager = std::make_unique<AssetManager>();
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

// void	Game::LoadLevel(int level)
// {
// // Add the systems that need to be processed in our game
// 	registry->AddSystem<MovementSystem>();
// 	registry->AddSystem<RenderSystem>();

// 	assetManager->AddTexture(renderer, "tank-image", "../assets/images/tank-panther-right.png");
//     assetManager->AddTexture(renderer, "jungle", "../assets/tilemaps/jungle.png");

// 	int tileSize = 32;
// 	double tileScale = 1.0;
// 	int assetWidth;
// 	int assetHeight;
// 	int mapNumCols;
// 	int mapNumRows;

// 	SDL_QueryTexture(assetManager->GetTexture("jungle"), NULL, NULL, &assetWidth, &assetHeight);
// 	mapNumCols = assetWidth / tileSize;
// 	mapNumRows = assetHeight / tileSize;

// 	std::fstream mapFile;
// 	mapFile.open("../assets/tilemaps/jungle.map");

// 	for (int y = 0; y < 25; y++)
// 	{
// 		for (int x = 0; x < 32; x++)
// 		{
// 			char ch;
// 			mapFile.get(ch);
// 			int srcRectY = std::atoi(&ch) * tileSize;
// 			mapFile.get(ch);
// 			int srcRectX = std::atoi(&ch) * tileSize;
// 			mapFile.ignore();
// 			Entity tile = registry->CreateEntity();
// 			tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
// 			tile.AddComponent<SpriteComponent>("jungle", tileSize, tileSize, srcRectX, srcRectY);
// 		}
// 	}
// 	mapFile.close();

// 	Entity tank = registry->CreateEntity();
// 	tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
// 	tank.AddComponent<SpriteComponent>("tank-image", 32, 32);
// 	tank.AddComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));

// }


void Game::LoadLevel(int level) {
    // Add the sytems that need to be processed in our game
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();

    // Adding assets to the asset store
    assetManager->AddTexture(renderer, "tank-image", "../assets/images/tank-panther-right.png");
    assetManager->AddTexture(renderer, "truck-image", "../assets/images/truck-ford-right.png");
    assetManager->AddTexture(renderer, "tilemap-image", "../assets/tilemaps/jungle.png");

    // Load the tilemap
    int tileSize = 32;
    double tileScale = 1.0;
    int mapNumCols = 1;
    static int mapNumRows = 0;
	std::string fileRow = "";
	size_t pos = 0;

    std::fstream mapFile;
    mapFile.open("../assets/tilemaps/jungle.map");
	
	while (getline(mapFile, fileRow))
	{
		while (pos < fileRow.size())
		{
			char ch;
			mapFile.get(ch);
			if (ch == ',')
				mapNumCols++;
			pos++;
		}
		mapNumRows++;
	}
	std::cout << "mapNumRows: " << std::to_string(mapNumRows) << std::endl;
	std::cout << "mapNumCols: " << std::to_string(mapNumCols) << std::endl;
	mapFile.close();

	mapFile.open("../assets/tilemaps/jungle.map");
    for (int y = 0; y < mapNumRows; y++) {
        for (int x = 0; x < mapNumCols; x++) {
            char ch;
            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * tileSize;
            mapFile.ignore();

            Entity tile = registry->CreateEntity();
            tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
            tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, srcRectX, srcRectY);
        }
    }
    mapFile.close();

    // Create an entity
    Entity tank = registry->CreateEntity();
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
    tank.AddComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32);

    Entity truck = registry->CreateEntity();
    truck.AddComponent<TransformComponent>(glm::vec2(50.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
    truck.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32);
}


void	Game::Setup()
{
	LoadLevel(1);
}

void	Game::Update()
{
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
		SDL_Delay(timeToWait);
	double deltaT = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

	// stores the "previous" frame time (ticks after the SDL_Delay)
	millisecsPreviousFrame = SDL_GetTicks();

	//Ask all the systems to update
	registry->GetSystem<MovementSystem>().Update(deltaT);

	//Update the registry to process the entities that are waiting to be created/killed
	registry->Update();
}

void	Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Invoke all the sysems that need to render
	registry->GetSystem<RenderSystem>().Update(renderer, assetManager);
	SDL_RenderPresent(renderer);
}

void	Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
