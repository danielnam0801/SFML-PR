#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include "Player.h"

void GameScene::Init()
{
	m_vecPlayer.push_back(std::make_shared<Player>(true));
	m_vecPlayer.push_back(std::make_shared<Player>(false));
}

void GameScene::Update(float _dt)
{
	for (size_t i = 0; i < m_vecPlayer.size(); i++)
	{
		m_vecPlayer[i]->Update(_dt);
	}
}

void GameScene::Render()
{
	WindowMgr::GetInst()->GetWindow().clear();
	for (size_t i; i < m_vecPlayer.size(); i++)
	{
		m_vecPlayer[i]->Render();
	}
	WindowMgr::GetInst()->GetWindow().display();
}
