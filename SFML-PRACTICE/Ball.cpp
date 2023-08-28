#include "Ball.h"

Ball::Ball(const sf::RenderWindow* _window)
{
	sf::Color color(rand() % 256, rand() % 256, rand() % 256);
	m_shape.setFillColor(color);
	m_shape.setRadius(rand() % 11 + 10);
	m_shape.setPosition(sf::Vector2f{
		(float)(rand() % _window->getSize().x - m_shape.getGlobalBounds().width)
		,(float)(rand() % _window->getSize().y - m_shape.getGlobalBounds().height)});
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
