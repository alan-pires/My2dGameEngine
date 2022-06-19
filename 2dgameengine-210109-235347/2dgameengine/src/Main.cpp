#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	Game game;

	game.Initialize();
	game.Run();
	game.Destroy();

	return 0;
}
