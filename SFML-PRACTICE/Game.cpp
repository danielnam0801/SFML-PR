#include "Game.h"
#include "Player.h"

Game::Game()
	: m_IsEndGame(false)
	, m_IsHoldmouse(false)
	, m_iScore(0)
	, m_iHp(10)
{
	Initvariable();
	InitWindow();
	m_window->setFramerateLimit(60);
}

Game::~Game()
{
	delete m_window;
}

void Game::UpdateCollision()
{
	for(size_t i = 0; i < m_vecBall.size(); ++i){
		if (m_player->GetRect().getGlobalBounds().intersects(m_vecBall[i].GetCircle().getGlobalBounds()));
		m_vecBall.erase(m_vecBall.begin() + i);
	}
}

void Game::Initvariable()
{
	m_player = new Player;
	m_window = nullptr;
	//enemys.push_back(Enemy(10, sf::Vector2f(10, 10), sf::Color::Red));
	//enemys.push_back(Enemy(8, sf::Vector2f(30, 30), sf::Color::Yellow));
	//enemys.push_back(Enemy(6, sf::Vector2f(50, 50), sf::Color::Green));
	//enemys.push_back(Enemy(10, sf::Vector2f(10, 10), sf::Color::Blue));
	//enemys.push_back(Enemy(10, sf::Vector2f(10, 10), sf::Color::Magenta));

	m_fEnemySpawnTimer = m_fEnemySpawnTimerMax = 10.0f;
	//m_iEnemyMax = 10;

	/*if (!m_font.loadFromFile("../Res/Font/Rubber-Duck.ttf"))
	{
		std::cout << "Font load Error" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("NONE");*/

}

void Game::InitWindow()
{
	m_videomode = { 1600, 900 };
	m_window = new sf::RenderWindow(m_videomode, "GAME 1");
	std::srand((unsigned int)time(NULL));
}

void Game::PollEvent()
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

void Game::SpawnEnemy()
{
	if (m_fEnemySpawnTimer < m_fEnemySpawnTimerMax)
		m_fEnemySpawnTimer += 1.f;
	else {
		if (m_vecBall.size() < m_iEnemyMax) {
			m_vecBall.push_back(Ball(m_window));
			m_fEnemySpawnTimer = 0.f;
		}
	}
}

void Game::UpdateEnemy()
{
}

void Game::RenderEnemy()
{

}

void Game::UpdateText()
{
	
}

void Game::RenderText(sf::RenderTarget& _target)
{
	_target.draw(m_text);
}

void Game::Update()
{
	PollEvent();
	SpawnEnemy();
	UpdateCollision();
	m_player->Update(m_window);
}

void Game::Render()
{
	m_window->clear();
	m_player->Render(m_window);
	for (auto& e : m_vecBall)
		e.Render(m_window);
	m_window->display();
}
