#include "Game.h"
#include "Player.h"
#include <iostream>
#include <sstream>
Game::Game()
	: m_iScore(0)
//	, m_iHp(10)
	, m_IsEndGame(false)
{
	Initvariable();
	InitWindow();
	m_window->setFramerateLimit(60);
	std::srand((unsigned int)time(nullptr));
}

Game::~Game()
{

}

void Game::UpdateCollision()
{
	for (size_t i = 0; i < m_vecBall.size(); ++i)
	{
		if (m_pPlayer->GetShape().getGlobalBounds().intersects(m_vecBall[i].GetShape().getGlobalBounds()))
		{
			switch (m_vecBall[i].GetType())
			{
			case BALLTYPE::DEFALUT:
				m_iScore++;
				break;
			case BALLTYPE::DAMAGE:
				m_pPlayer->TakeDamage(4);
				m_sound[1].play();
				break;
			case BALLTYPE::HEAL:
				m_pPlayer->GainHeal(3);
				m_sound[0].play();
				break;
			}
			m_vecBall.erase(m_vecBall.begin() + i);

		}

	}
}

void Game::Initvariable()
{
	m_pPlayer = new Player;
	m_window = nullptr;
	//m_enemy.setPosition(sf::Vector2f(50.f, 50.f));
	//m_enemy.setSize(sf::Vector2f(100.f, 100.f));
	//m_enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	//m_enemy.setFillColor(sf::Color::Cyan);
	//m_enemy.setOutlineColor(sf::Color::Blue);
	//m_enemy.setOutlineThickness(3.f);

	if (!m_font.loadFromFile("../Res/Font/IsiniScript.ttf"))
	{
		std::cout << "font error" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(60);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("");

	m_endtext.setFont(m_font);
	m_endtext.setCharacterSize(100);
	m_endtext.setFillColor(sf::Color(80, 188, 223));
	m_endtext.setPosition(sf::Vector2f(600,450));
	m_endtext.setString("GAME OVER!");

	m_fEnemySpawnTimerMax = 10.f;
	m_fEnemySpawnTimer = m_fEnemySpawnTimerMax;
	m_iEnemyMax = 10;

	m_playerhpbar.setSize(sf::Vector2f(225.f, 25.f));
	m_playerhpbar.setFillColor(sf::Color::Red);
	m_playerhpbar.setPosition(sf::Vector2f(sf::Vector2f(0.f, 130.f)));
	m_playerhpbarback = m_playerhpbar;
	m_playerhpbarback.setFillColor(sf::Color(25,25,25,200));

	if (!m_soundbuf[0].loadFromFile("../Res/Sound/Coin.wav"))
	{
		std::cout << "coin sound load error" << std::endl;
	}
	if (!m_soundbuf[1].loadFromFile("../Res/Sound/Hurt.wav"))
	{
		std::cout << "Hurt sound load error" << std::endl;
	}
	m_sound[0].setBuffer(m_soundbuf[0]);
	m_sound[1].setBuffer(m_soundbuf[1]);

	if (!m_bgm.openFromFile("../Res/Sound/bgm.mp3"))
	{
		std::cout << "bgm sound open error" << std::endl;
	}
	m_bgm.play();
	m_bgm.setLoop(true);
	//m_bgm.getStatus();
	//m_bgm.pause();
	//m_bgm.stop();
	//m_bgm.setVolume();
	//m_bgm.setPitch();
}

void Game::InitWindow()
{
	m_videomode = { 1600,900 };
	m_window = new sf::RenderWindow(m_videomode, "GAME 2");
}

void Game::PollEvent()
{
	while (m_window->pollEvent(m_eve))
	{
		switch (m_eve.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}
}

void Game::SpawnEnemy()
{
	if (m_fEnemySpawnTimer < m_fEnemySpawnTimerMax)
		m_fEnemySpawnTimer += 1.f;
	else
	{
		if (m_vecBall.size() < m_iEnemyMax)
		{
			m_vecBall.push_back(Ball(m_window, (BALLTYPE)(rand()%(int)BALLTYPE::END)));
			m_fEnemySpawnTimer = 0.f;
		}
	}
}

void Game::UpdateEnemy()
{
}

void Game::RenderEnemy()
{
	//for (auto& e : m_vecenemy)
	//	m_window->draw(e);
}

void Game::UpdateText()
{
	std::stringstream ss;
	ss << "Score: " << m_iScore << std::endl;
	ss << "HP: " << m_pPlayer->GetHp()
		<< " / " << m_pPlayer->GetHpMax() << std::endl;
	m_text.setString(ss.str());
}

void Game::RenderText(sf::RenderTarget& _target)
{
	_target.draw(m_text);
	_target.draw(m_playerhpbarback);
	_target.draw(m_playerhpbar);
}

void Game::UpdateGui()
{
	float fPercent = (float)(m_pPlayer->GetHp() / m_pPlayer->GetHpMax());
	if (m_playerhpbar.getSize().x > 200.f * fPercent)
	{
		float newsize = m_playerhpbar.getSize().x - 2.0f;
		m_playerhpbar.setSize(sf::Vector2f(newsize, m_playerhpbar.getSize().y));
	}
	else
	{
		float newsize = m_playerhpbar.getSize().x + 2.0f;
		m_playerhpbar.setSize(sf::Vector2f(newsize, m_playerhpbar.getSize().y));
	}
}

void Game::Update()
{
	PollEvent();
	//1
	if (m_IsEndGame == false)
	{
		SpawnEnemy();
		m_pPlayer->Update(m_window);
		UpdateCollision();
		UpdateText();
		UpdateGui();
		if (m_pPlayer->GetHp() <= 0)
			m_IsEndGame = true;
	}
}

void Game::Render()
{
	m_window->clear();
	// 플레이어 그리고.. 등등
	m_pPlayer->Render(m_window);
	for (auto& e : m_vecBall)
		e.Render(m_window);
	RenderText(*m_window);
	if (m_IsEndGame)
		m_window->draw(m_endtext);
	m_window->display();	
}
