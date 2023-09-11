#include "Core.h"
#include "define.h"
#include "IntroScene.h"
Core::Core(int _width, int _height, std::string _title)
{
	srand((unsigned int)time(nullptr));
	m_gamedata->Window.create(sf::VideoMode(_width, _height), _title);
	Init();
}

void Core::PollEvent()
{
	sf::Event eve;
	while (m_gamedata->Window.pollEvent(eve))
	{
		if (sf::Event::Closed == eve.type)
			m_gamedata->Window.close();
	}

}

void Core::Init()
{
	m_gamedata->Scenemgr.AddScene(std::make_unique<IntroScene>(m_gamedata));
	m_gamedata->Resmgr.LoadTexture("Intro Scene Background", INTRO_SCENE_BACKGROUND_FILEPATH);
}

void Core::Run()
{
	// 현재 시간을 받아오고,
	float curtime = m_clock.getElapsedTime().asSeconds();
	float newtime, frametime;
	float accumulator = 0.0f;
	while (m_gamedata->Window.isOpen())
	{
		m_gamedata->Scenemgr.ChangeScene();
		// 다음 시간을 받아와서
		newtime = m_clock.getElapsedTime().asSeconds();
		// 그 차이만큼 가지고 있고,
		frametime = newtime - curtime;
		// 현재시간을 갱신한 시간으로 바꾼다.
		curtime = newtime;
		accumulator += frametime;
		while (accumulator >= m_dt)
		{
			PollEvent();
			m_gamedata->Scenemgr.GetCurScene()->Update(m_dt);
			m_gamedata->Scenemgr.GetCurScene()->Render();
			accumulator -= m_dt;
		}
		//float interpolation = accumulator / m_dt;
		//m_gamedata->Scenemgr.GetCurScene()->Render(interpolation);
	}
}

