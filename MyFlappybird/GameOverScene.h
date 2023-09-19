#pragma once
#include "Scene.h"
#include "Core.h"
class GameOverScene : public Scene
{
public:
	GameOverScene(std::shared_ptr<GameData> _data, int score);
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Text		m_scoreTxt;
	sf::Text		m_highscoreTxt;
	sf::Sprite		m_background;
	sf::Sprite		m_title;
	sf::Sprite		m_body;
	sf::Sprite		m_button;
	int				m_highScore;
	int				m_Score;
};

