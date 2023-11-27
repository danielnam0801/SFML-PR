#include "pch.h"
#include "Core.h"
#include "WindowMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include <filesystem> //파일 시스템
Core::Core(int _width, int _height, std::string _title)
{
    srand((unsigned int)time(nullptr));
    WindowMgr::GetInst()->GetWindow().create(sf::VideoMode(_width, _height), _title, sf::Style::Close | sf::Style::Titlebar);
    Init();
}
void Core::Init()
{
    // ResMgr에 Font, Texture.. 담았습니다.
   // ResMgr::GetInst()->LoadTexture("Title", TITLE_FILEPATH);
    SceneMgr::GetInst()->Init();
    std::filesystem::directory_iterator("./Texture/")
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


void Core::PollEvent()
{
    sf::Event eve;
    while (WindowMgr::GetInst()->GetWindow().pollEvent(eve))
    {
        if (sf::Event::Closed == eve.type || sf::Event::KeyPressed == eve.type && sf::Keyboard::Escape == eve.key.code)
            WindowMgr::GetInst()->GetWindow().close();
    }
}

