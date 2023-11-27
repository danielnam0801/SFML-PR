#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
void GameScene::Init()
{
	m_rt.setFillColor(Color(Color::Red));
}

void GameScene::Update(float _dt)
{

}

void GameScene::Render()
{
	WindowMgr::GetInst()->GetWindow().clear();
	WindowMgr::GetInst()->GetWindow().draw(m_rt);
	WindowMgr::GetInst()->GetWindow().display();
} 
