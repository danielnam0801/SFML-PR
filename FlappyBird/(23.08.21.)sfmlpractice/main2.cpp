#include "Game.h"

int main()
{
	// ���� ���� �ʱ�ȭ
	Game game;
	while (game.GetIsRun())
	{
		game.Update(); 
		// 
		game.Render();
		//
	}
}