#include "Core.h"

int main()
{
	Core core;
	while (core.GetIsRun()) {
		core.Update();
		core.Render();
	}
}