#include "IntroScene.h"
#include "MainMenuScene.h"
#include "define.h"
#include<iostream>
IntroScene::IntroScene(std::shared_ptr<GameData> _gamedata)
	: m_gamedata(_gamedata)
{
}
void IntroScene::Init()
{
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Intro Scene Background"));
}

void IntroScene::Update(float _dt)
{
	// 애들아 INTRO_SHOW_TIME 이거 이용해서 3초 있다가 씬 변경하고 싶으면?
	int startalpha = 0;
	int endalpha = 255;
	static int curalpha = startalpha;
	m_background.setColor(sf::Color(255, 255, 255, curalpha));

	if (m_clock.getElapsedTime().asSeconds() > INTRO_SHOW_TIME && curalpha >=endalpha)
	{
		//		std::cout << "go to menu scene" << std::endl;
		m_gamedata->Scenemgr.AddScene(std::make_unique<MainMenuScene>(m_gamedata));
	}
	else
	//	curalpha = startalpha * m_clock.getElapsedTime().asSeconds() / INTRO_SHOW_TIME + endalpha;
		curalpha = endalpha * m_clock.getElapsedTime().asSeconds() / INTRO_SHOW_TIME;
	//	p=(d2)* p1 + d1 * p2;

}

void IntroScene::Render()
{
	// claer, draw, display
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.display();

}
