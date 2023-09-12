#include "GameScene.h"
#include "Pipe.h"
#include "Bird.h"
#include "Land.h"

GameScene::GameScene(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
{
	
}

GameScene::~GameScene()
{
	delete m_pPipe;
	delete m_pLand;
	delete m_pBird;
}

void GameScene::Init()
{
	m_background.setTexture(m_gameData->Resmgr.GetTexture("Main Scene Background"));
	m_pPipe = new Pipe(m_gameData);
	m_pLand = new Land(m_gameData);
	m_pBird = new Bird(m_gameData);
	m_pPipe->m_landHeight = m_pLand->landHeight;
}

void GameScene::Update(float _dt)
{
	m_pPipe ->Update(_dt);
	m_pLand ->Update(_dt);
	m_pBird ->Update(_dt);
}

void GameScene::Render()
{
	//sfml : clear -> draw -> display
	m_gameData->Window.clear();
	m_gameData->Window.draw(m_background);
	m_pPipe->Render();
	m_pLand->Render();
	m_pBird->Render();
	m_gameData->Window.display();
}
