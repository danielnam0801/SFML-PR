#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include "Player.h"

void GameScene::Init()
{
	m_vecPlayer.push_back(std::make_shared<Player>
	(
		sf::Keyboard::Key::W, sf::Keyboard::Key::S,
		sf::Keyboard::Key::A, sf::Keyboard::Key::D,
		sf::Keyboard::Key::Space, 
		3, 15, Vector2f{0,-1.f}, 2, 3)
	);
	m_vecPlayer.push_back(std::make_shared<Player>
	(
		sf::Keyboard::Key::Up, sf::Keyboard::Key::Down,
		sf::Keyboard::Key::Left, sf::Keyboard::Key::Right,
		sf::Keyboard::Key::RShift,
		3, 15, Vector2f{ 0,-1.f }, 2, 3)
	);
	m_vecEnemy.push_back(Enemy(
		Vector2f(WindowMgr::GetInst()->GetWindow().getSize().x / 2, 0), Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), ENEMY::MOVEDOWN, rand() % 3 + 1,
		1, 3));
	m_background.setTexture(ResMgr::GetInst()->GetTexture("BG01"));
	m_clock.restart();
}

void GameScene::Update(float _dt)
{
	PlayerUpdate(_dt);
	EnemyUpdate(_dt);
}

void GameScene::Render()
{
	WindowMgr::GetInst()->GetWindow().clear();
	WindowMgr::GetInst()->GetWindow().draw(m_background);
	for (size_t i = 0; i < m_vecPlayer.size(); i++)
	{
		m_vecPlayer[i]->Render();
	}for (size_t i = 0; i < m_vecEnemy.size(); i++)
	{
		m_vecEnemy[i].Render();
	}
	WindowMgr::GetInst()->GetWindow().display();
}

void GameScene::EnemyUpdate(float _dt)
{
	for (size_t i = 0; i < m_vecEnemy.size(); )
	{
		if (m_vecEnemy[i].Update(_dt))
		{
			m_vecEnemy.erase(m_vecEnemy.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void GameScene::PlayerUpdate(float _dt)
{
	for (size_t i = 0; i < m_vecPlayer.size(); i++)
	{
		m_vecPlayer[i]->Update(_dt);
	}
}

void GameScene::SpawnEnemy()
{
	if(m_clock.getElapsedTime().asSeconds() > spawnTime)
	{
		m_vecEnemy.push_back(Enemy(
			Vector2f(rand() % WindowMgr::GetInst()->GetWindow().getSize().x, 0), Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), ENEMY::MOVEDOWN, rand() % 3 + 1,
			1, 3));
		m_clock.restart();
	}
}
