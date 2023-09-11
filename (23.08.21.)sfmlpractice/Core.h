#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
class Core
{
private:
	sf::RenderWindow*				m_window;
	sf::Event						m_eve;
	sf::VideoMode					m_videomode;

	sf::RectangleShape				m_enemy;
	sf::Vector2i					m_mousepos;
	sf::Vector2f					m_mouseposview;
	std::vector<sf::RectangleShape> m_vecenemy;
	sf::Font						m_font;
	sf::Text						m_text;
private:
	float m_fEnemySpawnTimer;
	float m_fEnemySpawnTimerMax;
	int   m_iEnemyMax;
	bool  m_IsHoldmouse;
	int	  m_iScore;
	int   m_iHp;
	bool  m_IsEndGame;
public:
	Core();
	~Core();
private:
	void Initvariable();
	void InitWindow();
	void PollEvent();
	void UpdateMousePos();
	void SpawnEnemy(); // enemy »ý¼º
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

