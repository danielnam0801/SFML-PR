#pragma once
#include "SFML/Graphics.hpp"
class Player
{
private:
	sf::RectangleShape m_shape;
	float			   m_fmovespeed;
	sf::RenderWindow*  m_window;
public:
	Player(float _x = 0.f, float _y = 0.f);
	virtual ~Player();
public:
	const sf::RectangleShape GetRect() const { return m_shape; }
	void Update(sf::RenderWindow* _window);
	void Render(sf::RenderTarget* _target);
private:
	void UpdateInput();
	void UpdateWindowCollision(const sf::RenderWindow* _window);
};

