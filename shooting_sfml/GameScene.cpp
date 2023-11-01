#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
void GameScene::Init()
{
//	m_pPlayer = std::make_shared<Player>();
	// 1p
	m_vecPlayer.push_back(std::make_shared<Player>
		(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space,1));
	// 2p
	m_vecPlayer.push_back(std::make_shared<Player>
		(Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift,2));
	
	/*m_vecEnemy.push_back(Enemy(
	Vector2f(WindowMgr::GetInst()->GetWindow().getSize().x/2, 0),
		Vector2f(0.f,1.f),Vector2f(0.1f,0.1f),ENEMY::MOVEDOWN, rand() % 3 + 1, 
		1, 3));*/
	m_background.setTexture(ResMgr::GetInst()->GetTexture("BG01"));
	m_gameOverText.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
	m_gameOverText.setCharacterSize(60);
	m_gameOverText.setFillColor(Color::Red);
	m_gameOverText.setString("GAME OVER!!");
	m_gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void GameScene::Update(float _dt)
{
	if (m_vecPlayer.size() > 0)
	{
		PlayerUpdate(_dt);
		EnemyUpdate(_dt);
	}
//	m_pPlayer->Update(_dt);

	// Player Update
	//for (size_t i = 0; i < m_vecPlayer.size(); i++)
	//{
	//	m_vecPlayer[i]->Update(_dt);

		// Bullet Update
		/*for (size_t j = 0; j < m_vecPlayer[i]->GetBullet().size();)
		{
			m_vecplayer[i]->GetBullet()[j].m_vecbullet[i].Update(_dt);
			if (m_vecPlayer[i]->GetBullet()[j].GetSprite().getPosition().y < 0)
			{
				m_vecPlayer[i]->GetBullet().erase(m_vecPlayer[i]->GetBullet().begin() + j);
			}
			else
				j++;
		}*/
	//}
}

void GameScene::Render()
{
	WindowMgr::GetInst()->GetWindow().clear();
	WindowMgr::GetInst()->GetWindow().draw(m_background);
	//m_pPlayer->Render();
	for (auto& e : m_vecPlayer)
		e->Render();
	for (auto& e : m_vecEnemy)
		e.Render();
	if (m_vecPlayer.size() <= 0)
	{
		WindowMgr::GetInst()->GetWindow().draw(m_gameOverText);
	}

	WindowMgr::GetInst()->GetWindow().display();
}

void GameScene::EnemySpawnUpdate()
{
	if (m_clock.getElapsedTime().asSeconds() > 0.5f)
	{
		m_vecEnemy.push_back(Enemy(
		Vector2f(rand() % SCREEN_WIDTH, 0),Vector2f(0.f,1.f),
			Vector2f(0.1f,0.1f),ENEMY::FOLLOW, rand() % 3 + 1,1, 3,
			rand() % m_vecPlayer.size()));
		m_clock.restart();
	}
}
void GameScene::EnemyUpdate(float _dt)
{
	EnemySpawnUpdate();
	for (size_t i = 0; i < m_vecEnemy.size(); )
	{
		if (m_vecEnemy[i].Update(_dt, 
			m_vecPlayer[m_vecEnemy[i].GetFollownum()]->GetSprite().getPosition())
			|| m_vecEnemy[i].GetIsDead())
			m_vecEnemy.erase(m_vecEnemy.begin() + i);
		else
			i++;
	}
}

void GameScene::PlayerUpdate(float _dt)
{
	for (size_t i = 0; i < m_vecPlayer.size();)
	{
		if (m_vecPlayer[i]->IsAlive())
		{
			m_vecPlayer[i]->Update(_dt,m_vecEnemy);
			++i;
		}
		//else if (!m_vecPlayer[i]->IsAlive())
		else
		{
			m_vecPlayer.erase(m_vecPlayer.begin() + i);
		}
	}
}


