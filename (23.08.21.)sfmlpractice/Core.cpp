#include "Core.h"
#include<iostream> // input ouput stream
#include<sstream> // string stream
Core::Core()
	: m_IsHoldmouse(false)
	, m_iScore(0)
	, m_iHp(10)
	, m_IsEndGame(false)
{
	Initvariable();
	InitWindow();
	m_window->setFramerateLimit(60);
	std::srand((unsigned int)time(nullptr));
}

Core::~Core()
{
	delete m_window;
}

void Core::Initvariable()
{
	m_window = nullptr;
	m_enemy.setPosition(sf::Vector2f(50.f, 50.f));
	m_enemy.setSize(sf::Vector2f(100.f, 100.f));
	m_enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	m_enemy.setFillColor(sf::Color::Cyan);
	m_enemy.setOutlineColor(sf::Color::Blue);
	m_enemy.setOutlineThickness(3.f);

	m_fEnemySpawnTimerMax = 10.f;
	m_fEnemySpawnTimer = m_fEnemySpawnTimerMax;
	m_iEnemyMax = 10;

	if (!m_font.loadFromFile("../Res/Font/IsiniScript.ttf"))
	{
		std::cout << "font load error" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(60);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("none");
}

void Core::InitWindow()
{
	//m_videomode.height;
	//m_videomode.width;
	m_videomode = {1600,900};
	m_window = new sf::RenderWindow(m_videomode, "GAME 1");
}

void Core::PollEvent()
{
	while (m_window->pollEvent(m_eve))
	{
		switch (m_eve.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		//case sf::Event::KeyPressed:
		//	if (m_eve.key.code == sf::Keyboard::Escape)
		//		m_window->close();
			break;
		}
	}
}

void Core::UpdateMousePos()
{
	//std::cout << "Mouse pos: " <<
	//	sf::Mouse::getPosition(*m_window).x << " "
	//	<< sf::Mouse::getPosition(*m_window).y << std::endl;
	m_mousepos = sf::Mouse::getPosition(*m_window);
	m_mouseposview = m_window->mapPixelToCoords(m_mousepos);
}

void Core::SpawnEnemy()
{
	m_enemy.setPosition
	(
		(float)(rand() % (int)(m_window->getSize().x - m_enemy.getSize().x))
		,0.f);
	m_enemy.setFillColor(sf::Color::Green);
	m_vecenemy.push_back(m_enemy);
}

void Core::UpdateEnemy()
{
	if (m_vecenemy.size() < m_iEnemyMax)
	{
		if (m_fEnemySpawnTimer >= m_fEnemySpawnTimerMax)
		{
			SpawnEnemy();
			m_fEnemySpawnTimer = 0.f;
		}
		else
			m_fEnemySpawnTimer += 1.f;
	}
	//for (auto& e : m_vecenemy)
	//	e.move(0.0f, 0.5f);

	// 밑에 내려가면 지우기
	for (size_t i = 0; i < m_vecenemy.size(); ++i)
	{
		m_vecenemy[i].move(0.0f, 5.0f);
		// 
		if (m_vecenemy[i].getPosition().y > m_window->getSize().y)
		{
			m_vecenemy.erase(m_vecenemy.begin() + i);
			m_iHp -= 1;
			std::cout << "Hp: " << m_iHp << std::endl;
		}
	}

	// 1. 매프레임마다 마우스 위치에 있는지 확인한다.
	// 2. 마우스가 클릭되면 그걸 통해서 처리한다.

	// 왼쪽마우스 버튼으로 클릭하면 지우기
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_IsHoldmouse == false)
		{
			m_IsHoldmouse = true;
//			bool isdeleted = false;
			for (size_t i = 0; i < m_vecenemy.size(); ++i)
			{
				if (m_vecenemy[i].getGlobalBounds().contains(m_mouseposview))
				{
//					isdeleted = true;
					m_vecenemy.erase(m_vecenemy.begin() + i);
					m_iScore += 1;
					std::cout << "Score: " << m_iScore << std::endl;
				}
				//if (isdeleted)
				//	break;
			}
		}
	}
	else
		m_IsHoldmouse = false;
}

void Core::RenderEnemy()
{
	for (auto& e : m_vecenemy)
		m_window->draw(e);
}

void Core::UpdateText()
{
	std::stringstream ss;
	ss << "Score: " << m_iScore << std::endl;
	ss << "Hp: " << m_iHp << std::endl;
	m_text.setString(ss.str());
}

void Core::RenderText(sf::RenderTarget& _target)
{
//	_target.draw(m_text);
	m_window->draw(m_text);
}

void Core::Update()
{
	PollEvent();
	if (m_IsEndGame == false)
	{
		UpdateMousePos();
		UpdateEnemy();
		UpdateText();
	}
	if (m_iHp <= 0)
		m_IsEndGame = true;
}

void Core:: ()
{
	m_window->clear();
//	m_window->draw(m_enemy);
	RenderEnemy();
	RenderText(*m_window);
	m_window->display();
}
