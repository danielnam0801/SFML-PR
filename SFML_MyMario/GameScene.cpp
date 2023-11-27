#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include "Camera.h"
#include "Player.h"

void GameScene::Init()
{
	sf::Image image;
	image.loadFromFile("./Texture/map.png");
	m_map.CreateFromImage(image);

	m_rt.setFillColor(Color(Color::Red));
}

void GameScene::Update(float _dt)
{
	//float movespeed = 100.f;
	//Vector2f viewPos = Camera::GetInst()->GetPos();
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	//	movespeed *= 2;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	viewPos.x -= movespeed * _dt;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//	viewPos.x += movespeed * _dt;
}

void GameScene::Render()
{
	WindowMgr::GetInst()->GetWindow().clear();
	WindowMgr::GetInst()->GetWindow().draw(m_rt);
	WindowMgr::GetInst()->GetWindow().display();
} 
