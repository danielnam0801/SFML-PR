#include "IntroScene.h"
#include "define.h"
IntroScene::IntroScene(std::shared_ptr<GameData> _gamedata)
	: m_gamedata(_gamedata)
{
}
void IntroScene::Init()
{
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Intro Scene Background"));
}

void IntroScene::Update(float _dt)
{
}

void IntroScene::Render()
{
	// claer, draw, display
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.display();

}
