#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Ball.h"
class Player;
class Game
{
private:
	Player* m_player;
	std::vector<Ball> m_vecBall;
private:
	sf::RenderWindow* m_window;
	sf::Event							m_eve;
	sf::VideoMode						m_videomode;
	sf::SoundBuffer						m_soundbuf[2];
	sf::Sound							m_sound[2];
	sf::Music							m_bgm;
	//sf::RectangleShape					m_enemy;
	//std::vector<sf::RectangleShape>		m_vecenemy;
	sf::Font							m_font;
	sf::Text							m_text;
	sf::RectangleShape					m_hpbar;
	sf::RectangleShape					m_dynamicBar;
private:
	float m_fEnemySpawnTimer;
	float m_fEnemySpawnTimerMax;
	float m_dynamicRectSizeX;
	int	  m_iEnemyMax;
	int   m_iScore;
	int   m_iHp;
	int	  m_maxHp;
	int	  m_beforeHp;
	bool  m_hpDecresing;
	bool  m_IsHoldmouse;
	bool  m_IsEndGame;
public:
	Game();
	~Game();
private:
	void UpdateCollision();
	void Initvariable();
	void InitWindow();
	void PollEvent();
	void SpawnEnemy();
	void UpdateEnemy();
	void RenderEnemy();
	void UpdateText();
	void UpdateGUI();
	void RenderText(sf::RenderTarget& _target);
public:
	void Update();
	void Render();
public:
	const bool GetIsRun() const { return m_window->isOpen(); }
	const bool GetIsEnd() const { return m_IsEndGame; }
};
