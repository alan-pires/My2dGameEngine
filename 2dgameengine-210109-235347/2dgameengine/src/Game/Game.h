#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

const int FPS = 30;
const int MILLISECS_PER_FRAME = 1000/FPS;

class Game
{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		bool isRunning;
		int millisecsPreviousFrame = 0;
		std::unique_ptr<Registry> registry;

	public:
		Game();
		~Game();
		void	Initialize();
		void	Run();
		void	ProcessInput();
		void	Update();
		void	Render();
		void	Destroy();
		void	Setup();

		uint windowWidth;
		uint windowHeight;
};

#endif