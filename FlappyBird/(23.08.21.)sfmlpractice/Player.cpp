#include "Player.h"
#include<iostream>
Player::Player(float _x, float _y)
	: m_fmovespeed(10.f)
	, m_iHpMax(10)
	, m_iHP(5)
{
	m_shape.setPosition(_x, _y);
	m_shape.setSize(sf::Vector2f(100.f, 100.f));
//	m_shape.setFillColor(sf::Color::Cyan);
	if(!m_tex.loadFromFile("../Res/Texture/Player.png"))
	{
		std::cout << "texture load error" << std::endl;
	}
	m_shape.setTexture(&m_tex);
}

Player::~Player()
{
}

void Player::Update(sf::RenderWindow* _window)
{
	//2
	UpdateInput();
	UpdateWindowCollision(_window);
}

void Player::Render(sf::RenderTarget* _target)
{
	_target->draw(m_shape);
}

void Player::TakeDamage(const int& _damage)
{
	m_iHP -= _damage;
	if (m_iHP < 0)
		m_iHP = 0;
}

void Player::GainHeal(const int& _heal)
{
	m_iHP += _heal;
	if (m_iHP > m_iHpMax)
		m_iHP = m_iHpMax;
}

void Player::UpdateInput()
{
	// setposition, getglobalbounds, getsize
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_shape.move(-m_fmovespeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_shape.move(m_fmovespeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_shape.move(0.f, -m_fmovespeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_shape.move(0.f, m_fmovespeed);

}

void Player::UpdateWindowCollision(const sf::RenderWindow* _window)
{
	// 왼쪽
	if (m_shape.getGlobalBounds().left <= 0.f)
		m_shape.setPosition(0.f, m_shape.getPosition().y);

	// 오른쪽
	if (m_shape.getGlobalBounds().left + m_shape.getGlobalBounds().width
		> _window->getSize().x)
		m_shape.setPosition(_window->getSize().x - m_shape.getGlobalBounds().width
			,m_shape.getPosition().y);
	// 위
	if(m_shape.getGlobalBounds().top<=0.f)
		m_shape.setPosition(m_shape.getGlobalBounds().left, 0.f);
	// 아래
	if (m_shape.getGlobalBounds().top + m_shape.getGlobalBounds().height
		> _window->getSize().y)
		m_shape.setPosition(m_shape.getSize().x,
			_window->getSize().y - m_shape.getGlobalBounds().height);
	
}