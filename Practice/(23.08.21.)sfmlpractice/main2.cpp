#include "Game.h"

int main()
{
	// 게임 엔진 초기화
	Game game;
	while (game.GetIsRun())
	{
		game.Update(); 
		// 
		game.Render();
		//
	}
}