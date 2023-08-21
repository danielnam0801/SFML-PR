#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class Core
{
private:
	sf::RenderWindow* m_window;
	sf::Event m_eve;
	sf::VideoMode m_videomode;

	sf::RectangleShape m_enemy;
	sf::Vector2i m_mousepos;
public:
	Core();
	~Core();
private:
	void Initvariable();
	void InitWindow();
	void PollEvent();
	void UpdateMousePos();
public:
	void Update();
	void Render();
public:
	const bool GetIsRun() const { return m_window->isOpen(); }
};

