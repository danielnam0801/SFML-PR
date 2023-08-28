#include "Core.h"
#include <sstream>

Core::Core()
	: m_IsEndGame(false)
	, m_IsHoldmouse(false)
	, m_iScore(0)
	, m_iHp(10)
{
	Initvariable();
	InitWindow();
	m_window->setFramerateLimit(60);
}

Core::~Core()
{
	delete m_window;
}

void Core::Initvariable()
{
	m_window = nullptr;
	enemys.push_back(Enemy(10, sf::Vector2f(10, 10), sf::Color::Red));
	enemys.push_back(Enemy(8, sf::Vector2f(30, 30), sf::Color::Yellow));
	enemys.push_back(Enemy(6, sf::Vector2f(50, 50), sf::Color::Green));
	enemys.push_back(Enemy(10, sf::Vector2f(10, 10), sf::Color::Blue));
	enemys.push_back(Enemy(10, sf::Vector2f(10, 10), sf::Color::Magenta));

	m_fEnemySpawnTimer = m_fEnemySpawnTimerMax = 10.0f;
	m_iEnemyMax = 10;

	if (!m_font.loadFromFile("../Res/Font/Rubber-Duck.ttf"))
	{
		std::cout << "Font load Error" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("NONE");
}

void Core::InitWindow()
{
	m_videomode = { 1600, 900 };
	m_window = new sf::RenderWindow(m_videomode, "GAME 1");
	std::srand((unsigned int)time(NULL));
}

void Core::PollEvent()
{
	while (m_window->pollEvent(m_eve)) {

		switch (m_eve.type) {
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			if (m_eve.key.code == sf::Keyboard::Escape)
				m_window->close();
			break;
		}
	}
}

void Core::UpdateMousePos()
{
	m_mousepos = sf::Mouse::getPosition(*m_window);
	m_mouseposview = m_window->mapPixelToCoords(m_mousepos);
}

void Core::SpawnEnemy()
{
	int randNum = rand() % 5;
	Enemy enemy = enemys[randNum];
	enemy.setPosition(randX , 0);
	enemy.setFillColor(sf::Color::Cyan);
	enemy.setOutlineColor(sf::Color::Blue);
	enemy.setOutlineThickness(3.f);
	m_vecenmey.push_back(enemy);
}

void Core::UpdateEnemy()
{
	if (m_vecenmey.size() < m_iEnemyMax)
	{
		if (m_fEnemySpawnTimer > m_fEnemySpawnTimerMax) {
			SpawnEnemy();
			m_fEnemySpawnTimer = 0.f;
		}
		else
			m_fEnemySpawnTimer += 1.f;
	}
	
	for (size_t i = 0; i < m_vecenmey.size(); i++)
	{	
		m_vecenmey[i].move(0, 10.f);

		if (m_vecenmey[i].re.getPosition().y > m_window->getSize().y) {
		
			m_vecenmey.erase(m_vecenmey.begin() + i);
			m_iHp -= 1;
			std::cout << "Hp: " << m_iHp << std::endl;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		if (!m_IsHoldmouse){
			m_IsHoldmouse = true;
			for (size_t i = 0; i < m_vecenmey.size(); i++) {
				if (m_vecenmey[i].getGlobalBounds().contains(m_mouseposview)) {
					m_iScore += 1;
					std::cout << "Score: " << m_iScore << std::endl;
					m_vecenmey.erase(m_vecenmey.begin() + i);
				}
			}
		}
	}
	else {
		m_IsHoldmouse = false;
	}
}

void Core::RenderEnemy()
{
	for (auto& a : m_vecenmey) {
		m_window->draw(a);
	}
}

void Core::Update()
{
	PollEvent();
	if (m_IsEndGame == false) {
		UpdateMousePos();
		UpdateEnemy();
		UpdateText();
	}
	if (m_iHp <= 0) {
		m_IsEndGame = true;
	}
}

void Core::Render()
{
	m_window->clear();
	RenderEnemy();
	RenderText(*m_window);
	m_window->display();
}

void Core::UpdateText()
{
	std::stringstream ss;
	ss << "Score: " << m_iScore << std::endl;
	ss << "HP: " << m_iHp << std::endl;
	m_text.setString(ss.str());
}

void Core::RenderText(sf::RenderTarget& _target)
{
	_target.draw(m_text);
}
