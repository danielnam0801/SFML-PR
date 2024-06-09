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
	m_gamedata->Resmgr.LoadTexture("Sky Background", SKY_BACKGROUND_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Land", LAND_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Bird 1", BIRD_1_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Bird 2", BIRD_2_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Bird 3", BIRD_3_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Bird 4", BIRD_4_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Score Pipe", INVISIBLE_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
	m_gamedata->Resmgr.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
	m_gamedata->Resmgr.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
	m_gamedata->Resmgr.LoadSoundbuf("Hit Sound", HIT_SOUND_FILEPATH);
	m_gamedata->Resmgr.LoadSoundbuf("Wing Sound", WING_SOUND_FILEPATH);
	m_gamedata->Resmgr.LoadSoundbuf("Point Sound", POINT_SOUND_FILEPATH);
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

