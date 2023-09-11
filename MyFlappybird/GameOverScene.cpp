#include "GameOverScene.h"

GameOverScene::GameOverScene(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
{
}

void GameOverScene::Init()
{
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Main Scene Background"));
}

void GameOverScene::Update(float _dt)
{
}

void GameOverScene::Render()
{
}
