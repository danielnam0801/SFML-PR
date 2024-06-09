#include "Core.h"

int main()
{
	// 게임 엔진 초기화
	Core core;
	while (core.GetIsRun() && !core.GetIsEnd())
	{
		core.Update();
		core.Render();
	}
}