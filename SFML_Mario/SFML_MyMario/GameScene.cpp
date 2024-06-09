#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include "Camera.h"
#include "Player.h"
#include "Map.h"
#include "CollisionMgr.h"
GameScene::GameScene()
{
	m_map = new Map;
}
GameScene::~GameScene()
{
	delete m_map;
}
void GameScene::Init()
{
	m_bgm.openFromFile("Sound\\overworld.ogg");
	m_bgm.play();
	Camera::GetInst()->GetMainCam().setCenter(400, 300);
	Camera::GetInst()->GetMainCam().setSize(800, 600);
	m_map->CreateJsonBoard();

	//GET_WINDOW.mapPixelToCoords(¸¶¿ì½ºÁÂÇ¥);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER,OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER,OBJECT_GROUP::PIPE);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER,OBJECT_GROUP::PIPE);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MONSTER,OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MONSTER,OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MONSTER,OBJECT_GROUP::PIPE);
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

	Scene::Update(_dt);
}

void GameScene::Render()
{
	GET_WINDOW.clear();
	//GET_WINDOW.setView(Camera::GetInst()->
	//	GetWindowView(GET_WINDOW.getSize()));
	GET_WINDOW.setView(Camera::GetInst()->GetMainCam());
	m_map->Render();
	Scene::Render();
	GET_WINDOW.setView(GET_WINDOW.getDefaultView());
	GET_WINDOW.display();
} 
