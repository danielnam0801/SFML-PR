#pragma once
#include<SFML/Graphics.hpp>
#include "Scene.h"
#include "Core.h"
class IntroScene : public Scene
{
public:
	IntroScene(std::shared_ptr<GameData> _gamedata);
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Texture m_backgroundtex;
	sf::Sprite m_background;
	sf::Clock m_clock;
};

