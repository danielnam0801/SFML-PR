#include "pch.h"
#include "MenuScene.h"
#include "ResMgr.h"
#include "WindowMgr.h"
void MenuScene::Init()
{

}

void MenuScene::Update(float _dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
	{

	}
}

void MenuScene::Render()
{
	// clear - draw - display
	WindowMgr::GetInst()->GetWindow().clear();
	WindowMgr::GetInst()->GetWindow().display();
}
