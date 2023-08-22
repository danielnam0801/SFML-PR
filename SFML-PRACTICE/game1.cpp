#include "Core.h"

int main()
{
	Core core;
	while (core.GetIsRun() && !core.GetIsEnd()) {
		core.Update();
		core.Render();
	}
}