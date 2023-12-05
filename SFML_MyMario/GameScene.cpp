#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include "Camera.h"
#include "Player.h"
#include "Map.h"

void GameScene::Init()
{
	/*sf::Image image;
	image.loadFromFile("./Texture/map.png");*/
	//Camera::GetInst()->SetZoomLevel(500.f);
	//Camera::GetInst()->SetPos(Vector2f(100.f,100.f));
	//m_map.CreateFromImage(image);
	m_map = new Map;
	m_map->CreateJsonBoard();
	/*Object* pPlayer = new Player;
	pPlayer->SetName("Mario");
	pPlayer->GetSprite().setPosition(m_map.CreateFromImage(image));
	AddObject(pPlayer, OBJECT_GROUP::PLAYER);*/
}

void GameScene::Update(float _dt)
{
	//float movespeed = 100.f;
	//Vector2f viewpos = Camera::GetInst()->GetPos();
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	//	movespeed *= 2;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	viewpos.x -= movespeed * _dt;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//	viewpos.x += movespeed * _dt;
	//Camera::GetInst()->SetPos(viewpos);
	m_map->UpdateTileAnimation(_dt);
	Scene::Update(_dt);
}

void GameScene::Render()
{
	GET_WINDOW.clear();
	//GET_WINDOW.setView(Camera::GetInst()->
	//	GetWindowView(GET_WINDOW.getSize()));
	m_map->Render();
	Scene::Render();
	GET_WINDOW.display();
} 
