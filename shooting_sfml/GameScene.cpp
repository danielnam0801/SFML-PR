#include "pch.h"
#include "GameScene.h"
#include "WindowMgr.h"
void GameScene::Init()
{
//	m_pPlayer = std::make_shared<Player>();
	// 1p
	m_vecPlayer.push_back(std::make_shared<Player>
		(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space,Keyboard::LControl, 1));
	// 2p
	m_vecPlayer.push_back(std::make_shared<Player>
		(Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L, Keyboard::RShift,Keyboard::Enter,2));
	
	/*m_vecEnemy.push_back(Enemy(
	Vector2f(WindowMgr::GetInst()->GetWindow().getSize().x/2, 0),
		Vector2f(0.f,1.f),Vector2f(0.1f,0.1f),ENEMY::MOVEDOWN, rand() % 3 + 1, 
		1, 3));*/
	m_background.setTexture(ResMgr::GetInst()->GetTexture("BG01"));
	m_background.setColor(Color(255,255,255,128));
	m_gameOverText.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
	m_gameOverText.setCharacterSize(60);
	m_gameOverText.setFillColor(Color::Red);
	m_gameOverText.setString("GAME OVER!!");
	m_gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	m_scoreText = m_gameOverText;
	m_scoreText.setFillColor(Color::Yellow);
	m_scoreText.setCharacterSize(30);
	m_scoreText.setString("");
	m_scoreText.setPosition(10.f, 10.f);

	m_timertext = m_scoreText;
	m_timertext.setPosition(10.f, m_scoreText.getPosition().y+
						m_scoreText.getGlobalBounds().height * 4);
	m_eStage = GAME_STAGE::STAGE03;
	m_StageWave = 0;
	m_IsStageClear = true;
}

void GameScene::Update(float _dt)
{
	if (m_vecPlayer.size() > 0)
	{
		PlayerUpdate(_dt);
		EnemyUpdate(_dt);
		UiUpdate(_dt);
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
	for (auto& e : m_vecTextTag)
		e.Render();
	if (m_vecPlayer.size() <= 0)
	{
		WindowMgr::GetInst()->GetWindow().draw(m_gameOverText);
	}
	WindowMgr::GetInst()->GetWindow().draw(m_scoreText);
	WindowMgr::GetInst()->GetWindow().draw(m_timertext);
	WindowMgr::GetInst()->GetWindow().display();
}

void GameScene::EnemySpawnUpdate()
{
	if (m_IsStageClear)
	{
		int Stage = (int)m_eStage;
		m_eStage = (GAME_STAGE)(++Stage);
		m_vecTextTag.push_back(TextTag("Stage: "+ std::to_string(Stage),
			1.f, 30.f, Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5),
			Vector2f(1.f,0.f),Color::White,80, true));
		m_IsStageClear = false;
		m_StageWave = 0;
	}
	switch (m_eStage)
	{
	case GAME_STAGE::STAGE01:
	{
		if (m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			for (int i = 0; i < 4; ++i)
			{
				m_vecEnemy.push_back(Enemy(Vector2f(rand() % SCREEN_WIDTH, 10.f),
					Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), ENEMY::MOVEDOWN,
					rand() % 3 + 1, 1, 2, rand() % m_vecPlayer.size() % 2));
			}
			m_clock.restart();
			m_StageWave++;
		}
		if (m_StageWave >= 2)
			m_IsStageClear = true;
	}
		break;
	case GAME_STAGE::STAGE02:
	{
		if (m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			for (int i = 0; i < 6; ++i)
			{
				m_vecEnemy.push_back(Enemy(Vector2f(rand() % SCREEN_WIDTH, 10.f),
					Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), (ENEMY)(rand() % 2),
					rand() % 4 + 2, 2, 3, rand() % m_vecPlayer.size() % 2));
			}
			m_clock.restart();
			m_StageWave++;
		}
		if (m_StageWave >= 3)
			m_IsStageClear = true;
	}
		break;
	case GAME_STAGE::STAGE03:
	{
		if (m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			for (int i = 0; i < 8; ++i)
			{
				m_vecEnemy.push_back(Enemy(Vector2f(rand() % SCREEN_WIDTH, 10.f),
					Vector2f(0.f, 1.f), Vector2f(0.1f, 0.1f), (ENEMY)(rand() % 3),
					rand() % 4 + 2, 2, 3, rand() % m_vecPlayer.size() % 2));
			}
			m_clock.restart();
			m_StageWave++;
		}
		if (m_StageWave >= 4)
			m_IsStageClear = true;
	}
	break;
	case GAME_STAGE::ELITE:
	{
		m_vecEnemy.push_back(Enemy(Vector2f(SCREEN_WIDTH / 2, 100.f),
			Vector2f(1.f, 0.f), Vector2f(0.1f, 0.1f), ENEMY::ELITE,
			50, 3, 5, rand() % m_vecPlayer.size() % 2));
	}
		break;
	case GAME_STAGE::BOSS:
		break;
	}
}
void GameScene::UiUpdate(float _dt)
{
	if (m_vecPlayer.size() == 2)
	{
		m_scoreText.setString("Player 1 : " + std::to_string(m_vecPlayer[0]->GetScore())
		+ "\nPlayer 2: " + std::to_string(m_vecPlayer[1]->GetScore()));
		m_timertext.setString("Player 1)\n duraion time: " + std::to_string(m_vecPlayer[0]->GetTimer())
		+"\nPlayer 2)\n duration time: "+std::to_string(m_vecPlayer[1]->GetTimer()));
	}
	else
	{
		m_scoreText.setString("Player " + std::to_string(m_vecPlayer[0]->GetNum())
			+ std::to_string(m_vecPlayer[0]->GetScore()));
		m_timertext.setString("Player " + std::to_string(m_vecPlayer[0]->GetNum())
			+"\n duration time: " + std::to_string(m_vecPlayer[0]->GetTimer()));
	}

	for (size_t i = 0; i < m_vecTextTag.size();)
	{
		m_vecTextTag[i].Update(_dt);
		if (m_vecTextTag[i].GetIsErase())
			m_vecTextTag.erase(m_vecTextTag.begin() + i);
		else
			++i;
	}
	// 
}
void GameScene::EnemyUpdate(float _dt)
{
	if(m_vecEnemy.empty())
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
		else if (!m_vecPlayer[i]->IsAlive())
		{
			for (size_t j = 0; j < m_vecEnemy.size(); ++j)
			{
				// 적이 따라가는 번호랑 플레이어의 번호랑 같은지, 
				if (m_vecEnemy[j].GetFollownum() == m_vecPlayer[i]->GetNum()
					&& m_vecPlayer[i]->GetNum() != 0)
				{
					m_vecEnemy[j].SetFollownum((m_vecEnemy[j].GetFollownum() + 1) % 2);
				}
				// 0번( 1Player 죽었다.) 
				else if(m_vecPlayer[i]->GetNum() == 0)
				{
					m_vecEnemy[j].SetFollownum(m_vecEnemy[j].GetFollownum() - 1);
				}
			}
			m_vecPlayer.erase(m_vecPlayer.begin() + i);
		}
	}
}


