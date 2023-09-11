#pragma once
// InputMgr, ResMgr, SceneMgr
// struct vs class 
#include<SFML/Graphics.hpp>
#include "InputMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
struct GameData
{
	InputMgr Inputmgr;
	ResMgr	 Resmgr;
	SceneMgr Scenemgr;
	sf::RenderWindow Window;
};
class Core
{
public:
	Core(int _width, int _height, std::string _title);
	void Init();
	void Run();
private:
	void PollEvent();
	std::shared_ptr<GameData> m_gamedata = std::make_shared<GameData>();
	sf::Clock m_clock;
	const float m_dt = 1.0f / 60.0f;
};

