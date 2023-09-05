#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

struct GameData
{
	InputManager	 InputManager;
	SceneManager	 SceneManager;
	ResourceManager  ResourceManager;
	sf::RenderWindow Window;
};

class Core
{
public:
	Core(int _width, int _height, std::string _title);
	void Init();
	void Run();
private:
	std::shared_ptr<GameData> m_gamedata = std::make_shared<GameData>();
	void PollEvent();
	sf::Clock m_clock;
	const float m_dt = 1.0f / 60.f;
};

