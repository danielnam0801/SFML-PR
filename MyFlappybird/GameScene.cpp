#include "GameScene.h"
#include "Pipe.h"

GameScene::GameScene(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
{
	
}

void GameScene::Init()
{
	m_background.setTexture(m_gameData->Resmgr.GetTexture("Main Scene Background"));
	m_pPipe = new Pipe(m_gameData);
}

void GameScene::Update(float _dt)
{
	m_pPipe ->Update(_dt);
}

void GameScene::Render()
{
	m_gameData->Window.clear();
	m_gameData->Window.draw(m_background);
	m_pPipe->Render();
	m_gameData->Window.display();
}
