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
	m_gamedata->Resmgr.LoadTexture("Title", MAIN_SCENE_TITLE_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("PlayButton", MAIN_SCENE_PLAYBUTTON_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Main Scene Background", MAIN_SCENE_BACKGROUND_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);

}

void Core::Run()
{
	// ���� �ð��� �޾ƿ���,
	float curtime = m_clock.getElapsedTime().asSeconds();
	float newtime, frametime;
	float accumulator = 0.0f;
	while (m_gamedata->Window.isOpen())
	{
		m_gamedata->Scenemgr.ChangeScene();
		// ���� �ð��� �޾ƿͼ�
		newtime = m_clock.getElapsedTime().asSeconds();
		// �� ���̸�ŭ ������ �ְ�,
		frametime = newtime - curtime;
		// ����ð��� ������ �ð����� �ٲ۴�.
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
