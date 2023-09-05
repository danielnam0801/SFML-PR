#pragma once
#include <SFML/Graphics.hpp>
#include "Core.h"
#include "Scene.h"
class IntroScene : public Scene
{
public:
	IntroScene(std::shared_ptr<GameData> _gamedata);
	void Init() override;
	void Update(float dt) override;
	void Render() override;
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Texture m_backgroundtex;
	sf::Sprite m_background;
};

