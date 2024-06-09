#include "Ball.h"

Ball::Ball(const sf::RenderWindow* _window, BALLTYPE _eType)
	: m_eType(_eType)

{
	m_shape.setRadius(rand() % 11 + 10); // 10 ~20
	m_shape.setPosition(sf::Vector2f(
		(float)(rand() % _window->getSize().x - m_shape.getGlobalBounds().width)
		, (float)(rand() % _window->getSize().y - m_shape.getGlobalBounds().height)));

	sf::Color color;
	switch (m_eType)
	{
	case BALLTYPE::DEFALUT:
		color = sf::Color::Cyan;
		break;
	case BALLTYPE::DAMAGE:
		color = sf::Color::Red;
		m_shape.setOutlineColor(sf::Color::White);
		m_shape.setOutlineThickness(3.f);
		break;
	case BALLTYPE::HEAL:
		color = sf::Color::Green;
		m_shape.setOutlineColor(sf::Color::White);
		m_shape.setOutlineThickness(3.f);
		break;
	}
	m_shape.setFillColor(color);
	//sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	//m_shape.setFillColor(color);

}

Ball::~Ball()
{
}

void Ball::Update()
{
}

void Ball::Render(sf::RenderTarget* _target)
{
	_target->draw(m_shape);
}
