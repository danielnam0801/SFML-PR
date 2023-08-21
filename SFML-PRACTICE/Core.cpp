#include "Core.h"

Core::Core()
{
	Initvariable();
	InitWindow();
}

Core::~Core()
{
	delete m_window;
}

void Core::Initvariable()
{
	m_window = nullptr;
	m_enemy.setPosition(sf::Vector2f(50.0f, 50.0f));
	m_enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	m_enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	m_enemy.setFillColor(sf::Color::Cyan);
	m_enemy.setOutlineColor(sf::Color::Blue);
	m_enemy.setOutlineThickness(3.f);
}

void Core::InitWindow()
{
	m_videomode = { 1600, 900 };
	m_window = new sf::RenderWindow(m_videomode, "GAME 1");
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
	std::cout << "Mouse pos: " <<
		sf::Mouse::getPosition(*m_window).x << " "
		<< sf::Mouse::getPosition(*m_window).y << std::endl;
}

void Core::Update()
{
	PollEvent();
	UpdateMousePos();
}

void Core::Render()
{
	m_window->clear();
	m_window->draw(m_enemy);
	m_window->display();
}
