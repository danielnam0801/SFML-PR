#include "Core.h"

int main()
{
	// ���� ���� �ʱ�ȭ
	Core core;
	while (core.GetIsRun() && !core.GetIsEnd())
	{
		core.Update();
		core.Render();
	}
}