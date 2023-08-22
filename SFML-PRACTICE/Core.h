#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>

enum Enemys
{
	Red,
	Yellow,
	Green,
	Blue,
	Magenta
};

class Enemy
{
private:
	sf::RectangleShape rect;
	int score;
public: 
	Enemy(int score, sf::Vector2f size, sf::Color color) {
		score = score;
		rect.setSize(size);
		rect.setFillColor(color);
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(3.f);
	}
	const sf::RectangleShape const GetRect( return rect );
	const int const GetScore( return score );
};

class Core
{
private:
	sf::RenderWindow*					m_window;
	sf::Event							m_eve;
	sf::VideoMode						m_videomode;

	sf::Vector2i						m_mousepos;
	sf::Vector2f						m_mouseposview;
	sf::Font							m_font;
	sf::Text							m_text;
	std::vector<Enemy> m_vecenmey;
private:
	float m_fEnemySpawnTimer;
	float m_fEnemySpawnTimerMax;
	int	  m_iEnemyMax;
	int	  m_iScore;
	int	  m_iHp;
	bool  m_IsHoldmouse;
	bool  m_IsEndGame;
public:
	Core();
	~Core();
private:
	void Initvariable();
	void InitWindow();
	void PollEvent();
	void UpdateMousePos();
	void SpawnEnemy();
	void UpdateEnemy();
	void RenderEnemy();
	void UpdateText();
	void RenderText(sf::RenderTarget& _target);
public:
	void Update();
	void Render();
public:
	const bool GetIsRun() const { return m_window->isOpen(); }
	const bool GetIsEnd() const { return m_IsEndGame; }
};

