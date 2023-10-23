#include "pch.h"
#include "Core.h"
#include "WindowMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"

Core::Core(int _width, int _height, std::string _title)
{
    srand((unsigned int)time(nullptr));
    WindowMgr::GetInst()->GetWindow().create(sf::VideoMode(_width, _height), _title, sf::Style::Close | sf::Style::Titlebar);
    Init();
}

void Core::Run()
{
    float newTime, frameTime;
    float curtime = m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;
    while (WindowMgr::GetInst()->GetWindow().isOpen())
    {
        newTime = m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - curtime;
        if (frameTime > 0.25f)
            frameTime = 0.25f;
        curtime = newTime;
        accumulator += frameTime;
        while (accumulator >= m_dt)
        {
            PollEvent();
            //Update(m_dt);
            //Render();
            SceneMgr::GetInst()->Update(m_dt);
            SceneMgr::GetInst()->Render();
            accumulator -= m_dt;
        }
    }
}

void Core::Update(const float& _dt)
{
}

void Core::Render()
{

}

void Core::PollEvent()
{
    sf::Event eve;
    while (WindowMgr::GetInst()->GetWindow().pollEvent(eve))
    {
        if (sf::Event::Closed == eve.type || sf::Event::KeyPressed == eve.type && sf::Keyboard::Escape == eve.key.code)
            WindowMgr::GetInst()->GetWindow().close();
    }
}

void Core::Init()
{
    // ResMgr에 Font, Texture.. 담았습니다.
    ResMgr::GetInst()->LoadTexture("Title", TITLE_FILEPATH);
    ResMgr::GetInst()->LoadTexture("Background", BACKGROUND_FILEPATH);
    ResMgr::GetInst()->LoadTexture("Button1", BUTTON1_FILEPATH);
    ResMgr::GetInst()->LoadTexture("Button2", BUTTON2_FILEPATH);
    ResMgr::GetInst()->LoadTexture("Exit", EXIT_FILEPATH);

    ResMgr::GetInst()->LoadTexture("Player", PLAYER_FILEPATH);
    ResMgr::GetInst()->LoadTexture("Bullet", BULLET_FILEPATH);
    ResMgr::GetInst()->LoadTexture("Front Gun", FRONTGUN_FILEPATH);

    ResMgr::GetInst()->LoadTexture("Font", FONT_FILEPATH);

    SceneMgr::GetInst()->Init();
}

