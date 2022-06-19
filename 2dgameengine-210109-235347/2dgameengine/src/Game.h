#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>

class Game
{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		bool isRunning;

	public:
		Game();
		~Game();
		void	Initialize();
		void	Run();
		void	ProcessInput();
		void	Update();
		void	Render();
		void	Destroy();
};

#endif