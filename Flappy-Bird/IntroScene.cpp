#include "IntroScene.h"
#include "define.h"

IntroScene::IntroScene(std::shared_ptr<GameData> _gamedata)
	:m_gamedata(_gamedata)
{
}

void IntroScene::Init()
{
	m_background.setTexture(m_gamedata->ResourceManager.GetTexture("Intro Scene Background"));
}

void IntroScene::Update(float dt)
{

}

void IntroScene::Render()
{
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.display();

}
