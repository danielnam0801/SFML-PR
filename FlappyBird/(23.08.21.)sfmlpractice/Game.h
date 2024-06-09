#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<vector>
#include "Ball.h"
//#include "Player.h" 1
class Player; // 2
class Game
{
private:
	Player*				m_pPlayer;
	std::vector<Ball>	m_vecBall;
	sf::RectangleShape  m_playerhpbar;
	sf::RectangleShape  m_playerhpbarback;
private:
	sf::RenderWindow*				m_window;
	sf::Event						m_eve;
	sf::VideoMode					m_videomode;
	sf::SoundBuffer m_soundbuf[2]; // texture
	sf::Sound m_sound[2]; // shape(sprite)
	sf::Music m_bgm; 

	//sf::RectangleShape				m_enemy;
	//std::vector<sf::RectangleShape> m_vecenemy;
	sf::Font						m_font;
	sf::Text						m_text;
	sf::Text						m_endtext;
private:
	float m_fEnemySpawnTimer;
	float m_fEnemySpawnTimerMax;
	int   m_iEnemyMax;
	int	  m_iScore;
//	int   m_iHp;
	bool  m_IsEndGame;
public:
	Game();
	~Game();
private:
	void UpdateCollision();
	void Initvariable();
	void InitWindow();
	void PollEvent();
	void SpawnEnemy(); // enemy »ý¼º
	void UpdateEnemy();
	void RenderEnemy();
	void UpdateText();
	void RenderText(sf::RenderTarget& _target);
	void UpdateGui();
public:
	void Update();
	void Render();
public:
	const bool GetIsRun() const { return m_window->isOpen(); }
	const bool GetIsEnd() const { return m_IsEndGame; }
};

