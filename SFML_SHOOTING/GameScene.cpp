#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include "Player.h"

void GameScene::Init()
{
	m_pPlayer = std::make_shared<Player>(true);
	m_pPlayer2 = std::make_shared<Player>(false);
}

void GameScene::Update(float _dt)
{
	m_pPlayer->Update(_dt);
	m_pPlayer2->Update(_dt);
}

void GameScene::Render()
{
	WindowMgr::GetInst()->GetWindow().clear();
	m_pPlayer->Render();
	m_pPlayer2->Render();
	WindowMgr::GetInst()->GetWindow().display();
}
