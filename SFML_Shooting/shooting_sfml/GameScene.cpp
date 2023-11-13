#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
#include <sstream>
void GameScene::Init()
{
//	m_pPlayer = std::make_shared<Player>();
	// 1p
	m_vecPlayer.push_back(std::make_shared<Player>
		(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space, Keyboard::LControl, 1));
	// 2p
	m_vecPlayer.push_back(std::make_shared<Player>
		(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right, Keyboard::Return, Keyboard::L, 2));
	
	/*m_vecEnemy.push_back(Enemy(
	Vector2f(WindowMgr::GetInst()->GetWindow().getSize().x/2, 0),
		Vector2f(0.f,1.f),Vector2f(0.1f,0.1f),ENEMY::MOVEDOWN, rand() % 3 + 1, 
		1, 3));*/
	m_background.setTexture(ResMgr::GetInst()->GetTexture("BG01"));
	m_background.setColor(Color(255,255,255,128));
	m_gameInfoText.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
	m_gameInfoText.setStyle(sf::Text::Bold);
	m_gameInfoText.setCharacterSize(30);
	m_gameInfoText.setPosition(10.f, 10.f);
	m_gameOverText.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
	m_gameOverText.setCharacterSize(60);
	m_gameOverText.setFillColor(Color::Red);
	m_gameOverText.setString("GAME OVER!!");
	m_gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	m_gameStage = GAME_STAGE::NONE;
	m_stageWave = 0;
	m_IsStageClear = true;
}

void GameScene::Update(float _dt)
{
	if (m_vecPlayer.size() > 0)
	{
		PlayerUpdate(_dt);
		EnemyUpdate(_dt);
		UIUpdate();
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
	WindowMgr::GetInst()->GetWindow().draw(m_gameInfoText);
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
	if ( m_IsStageClear)
	{
		int stage = (int)m_gameStage;
		m_gameStage = (GAME_STAGE)(++stage);
		m_vecTextTag.push_back(TextTag("Stage: " + std::to_string(stage), 1.f, 30.f,
			Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5),
			Vector2f(1.f, 0.f), Color::White, 80, true));
		m_IsStageClear = false;
		m_stageWave = 0;
	}
	switch (m_gameStage)
	{
	case GAME_STAGE::STAGE01:
		if (m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			for (int i = 0; i < 4; ++i)
			{
				m_vecEnemy.push_back(Enemy(Vector2f(rand() % SCREEN_WIDTH, 10.f),
					Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), ENEMY::MOVEDOWN,
					rand() % 3 + 1, 1, 2, rand() % m_vecPlayer.size() % 2));
			}
			m_clock.restart();
			m_stageWave++;
		}
		if(m_stageWave >= 2)
		{
			m_IsStageClear = true;
		}
		break;
	case GAME_STAGE::STAGE02:
		if (m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			for (int i = 0; i < 6; ++i)
			{
				m_vecEnemy.push_back(Enemy(Vector2f(rand() % SCREEN_WIDTH, 10.f),
					Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), (ENEMY)(rand() % 2),
					rand() % 4 + 2, 2, 3, rand() % m_vecPlayer.size() % 2));
			}
			m_clock.restart();
			m_stageWave++;
		}
		if (m_stageWave >= 3)
		{
			m_IsStageClear = true;
		}
		break;
	case GAME_STAGE::STAGE03:
		if (m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			for (int i = 0; i < 4; ++i)
			{
				m_vecEnemy.push_back(Enemy(Vector2f(rand() % SCREEN_WIDTH, 10.f),
					Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), ENEMY(rand()%4),
					rand() % 4 + 2, 2, 3, rand() % m_vecPlayer.size() % 2));
			}
			m_clock.restart();
			m_stageWave++;
		}
		if (m_stageWave >= 4)
		{
			m_IsStageClear = true;
		}
		break;
	case GAME_STAGE::ELITE:
		m_vecEnemy.push_back(Enemy(Vector2f(SCREEN_WIDTH / 2, 100.f),
			Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), ENEMY(rand() % 4),
			rand() % 4 + 2, 2, 3, rand() % m_vecPlayer.size() % 2));
		break;
	case GAME_STAGE::BOSS:
		break;
	case GAME_STAGE::END:
		break;
	default:
		break;
	}
	
	if (m_clock.getElapsedTime().asSeconds() > 0.5f)
	{
		m_vecEnemy.push_back(Enemy(
		Vector2f(rand() % SCREEN_WIDTH, 0),Vector2f(0.f,1.f),
			Vector2f(0.1f,0.1f),(ENEMY)(rand() % 3), rand() % 3 + 1, 1, 3,
			rand() % m_vecPlayer.size()));

		m_clock.restart();
	}
}
void GameScene::UIUpdate()
{
	if (m_vecPlayer.size() == 2)
	{
		m_gameInfoText.setString("Player1 : " + std::to_string(m_vecPlayer[0]->GetScore()) + "\n"
			+ "Player2 : " + std::to_string(m_vecPlayer[1]->GetScore()) + "\n"
			+ "Timer1 : " + std::to_string(m_vecPlayer[0]->GetTimer()) + "\n"
			+ "Timer2 : " + std::to_string(m_vecPlayer[1]->GetTimer()) + "\n"
		);
	}
	else
	{
		m_gameInfoText.setString("Player " + std::to_string(m_vecPlayer[0]->GetNum())
			+ std::to_string(m_vecPlayer[0]->GetScore())
			+ "Timer : " + std::to_string(m_vecPlayer[0]->GetTimer()) + "\n"
		);
	}

	for (size_t i = 0; i < m_vecTextTag.size();)
	{
		if (m_vecTextTag[i].GetIsErase())
		{
			m_vecTextTag.erase(m_vecTextTag.begin() + i);
		}
		else
			i++;
	}

	
}
void GameScene::EnemyUpdate(float _dt){

	if (m_vecEnemy.empty())
		EnemySpawnUpdate(); 
	for (size_t i = 0; i < m_vecEnemy.size(); )
	{
		if (m_vecPlayer.size() < 2)
			m_vecEnemy[i].SetFollownum(0);

		if (m_vecEnemy[i].Update(_dt, m_vecPlayer[m_vecEnemy[i].GetFollownum()]->GetSprite().getPosition())
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
		else if (!m_vecPlayer[i]->IsAlive())
		{
			for (size_t j = 0; j < m_vecEnemy.size(); j++)
			{
				if (m_vecEnemy[j].GetFollownum() == m_vecPlayer[i]->GetNum()
					&& m_vecPlayer[i]->GetNum() != 0)
				{
					m_vecEnemy[j].SetFollownum((m_vecEnemy[j].GetFollownum() + 1) % 2);
				}
				else if (m_vecPlayer[i]->GetNum() == 0)
				{
					m_vecEnemy[j].SetFollownum(m_vecEnemy[j].GetFollownum() - 1);
				}
			}
			m_vecPlayer.erase(m_vecPlayer.begin() + i);
		}
	}
}


