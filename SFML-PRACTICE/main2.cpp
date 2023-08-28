#include "Game.h"

int main()
{
	Game game;
	while (game.GetIsRun() && !game.GetIsEnd()) {
		game.Update();
		game.Render();
	}
}