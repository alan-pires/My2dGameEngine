#include <iostream>
#include "../Game/Game.h"
#include "../Logger/Logger.h"

using namespace std;

int main()
{
	Game game;

	game.Initialize();
	game.Run();
	game.Destroy();

	return 0;
}
