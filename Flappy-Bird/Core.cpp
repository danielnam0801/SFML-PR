#include "Core.h"
#include "define.h"
#include "IntroScene.h"
#include <time.h>

Core::Core(int _width, int _height, std::string _title)
{
	srand((unsigned int)time(NULL));
	m_gamedata->Window.create(sf::VideoMode(_width, _height), _title);
	Init();
}

void Core::Init()
{
	m_gamedata->SceneManager.AddScene(std::make_unique<IntroScene>(m_gamedata));
	m_gamedata->ResourceManager.LoadTexture("Intro Scene Background", INTRO_SCENE_BACKGROUND_FILEPATH);
 }

void Core::Run()
{
	//���� �ð��� �޾ƿ���
	float curtime = m_clock.getElapsedTime().asSeconds();
	float newtime, frametime;
	float accumulator = 0.0f;
	while(m_gamedata -> Window.isOpen())
	{
		m_gamedata->SceneManager.ChangeScene();
		//���� �ð��� �޾ƿͼ�
		newtime = m_clock.getElapsedTime().asSeconds();
		//�� ���̸�ŭ ������ �ְ�
		frametime = newtime - curtime;
		//���� �ð��� ������ �ð����� �ٲ۴�
		curtime = newtime;
		accumulator += frametime;
		while (accumulator >= m_dt) {
			PollEvent();
			m_gamedata->SceneManager.GetCurScene()->Update(m_dt);
			m_gamedata->SceneManager.GetCurScene()->Render();
			accumulator -= m_dt;
		}
	}
}

void Core::PollEvent()
{
	sf::Event eve;
	while (m_gamedata->Window.pollEvent(eve)) 
	{
		if (sf::Event::Closed == eve.type) {
			m_gamedata->Window.close();
		}
	}
}
