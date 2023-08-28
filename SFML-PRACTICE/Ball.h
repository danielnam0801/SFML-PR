#pragma once
#include<SFML/Graphics.hpp>
class Ball
{
private:
	sf::CircleShape m_shape;
public:
	Ball(const sf::RenderWindow* _window);
	virtual ~Ball();
public:
	const sf::CircleShape GetCircle() const { return m_shape; }
	void Update();
	void Render(sf::RenderTarget* _target);
};

