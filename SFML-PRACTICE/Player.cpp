#include "Player.h"
#include<iostream>

Player::Player(float _x, float _y)
	:m_fmovespeed(10.f)
{
	m_shape.setPosition(_x, _y);
	m_shape.setSize(sf::Vector2f(100.f, 100.f));
	m_shape.setFillColor(sf::Color::Cyan);

	if (!m_tex.loadFromFile("../Res/Texture/Player.png")) {
		std::cout << "texture load error" << std::endl;
	}
	m_shape.setTexture(&m_tex);
}

Player::~Player()
{
}

void Player::Update(sf::RenderWindow* _window)
{
	UpdateWindowCollision(_window);
	UpdateInput();
}

void Player::Render(sf::RenderTarget* _target)
{
	_target->draw(m_shape);
}

void Player::UpdateInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_shape.move(-m_fmovespeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_shape.move(m_fmovespeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_shape.move(0.f, -m_fmovespeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_shape.move(0.f, m_fmovespeed);
	
}

void Player::UpdateWindowCollision(const sf::RenderWindow* m_window)
{
	if (m_shape.getGlobalBounds().left <= 0)
		m_shape.setPosition( 0, m_shape.getPosition().y );
	if (m_shape.getGlobalBounds().left + m_shape.getGlobalBounds().width > m_window->getSize().x)
		m_shape.setPosition( m_window->getSize().x - m_shape.getGlobalBounds().width, m_shape.getPosition().y );
	if (m_shape.getGlobalBounds().top < 0)
		m_shape.setPosition( m_shape.getGlobalBounds().left, 0 );
	if (m_shape.getGlobalBounds().top + m_shape.getGlobalBounds().height > m_window->getSize().y)
		m_shape.setPosition( m_shape.getGlobalBounds().left , m_window->getSize().y - m_shape.getGlobalBounds().height );
}

