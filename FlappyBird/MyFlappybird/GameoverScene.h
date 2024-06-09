#pragma once
#include "Scene.h"
#include "Core.h"
class GameoverScene : public Scene
{
public:
	GameoverScene(std::shared_ptr<GameData> _data, int _score);
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Sprite m_background;
	sf::Sprite m_title;
	sf::Sprite m_body;
	sf::Sprite m_button;
	sf::Text m_scoreText;
	sf::Text m_highscoreText;
	int		 m_highScore;
	int		 m_Score;
};

