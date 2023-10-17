#include "pch.h"
#include "MenuScene.h"
#include "ResMgr.h"
#include "WindowMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"

void MenuScene::Init()
{
    m_background.setTexture(ResMgr::GetInst()->GetTexture("Background"));
    m_title.setTexture(ResMgr::GetInst()->GetTexture("Title"));
    m_button1.setTexture(ResMgr::GetInst()->GetTexture("Button1"));
    m_button2.setTexture(ResMgr::GetInst()->GetTexture("Button2"));
    m_buttonexit.setTexture(ResMgr::GetInst()->GetTexture("Exit"));

    m_title.setScale(0.7f, 0.7f);
    m_title.setPosition(
        WindowMgr::GetInst()->GetWindow().getSize().x / 2 - m_title.getGlobalBounds().width / 2
        , m_title.getGlobalBounds().height / 2);
    m_button1.setPosition(WindowMgr::GetInst()->GetWindow().getSize().x / 2
        - m_button1.getGlobalBounds().width / 2
        , WindowMgr::GetInst()->GetWindow().getSize().y / 2
        - m_button1.getGlobalBounds().height / 2);
    m_button2.setPosition(WindowMgr::GetInst()->GetWindow().getSize().x / 2
        - m_button2.getGlobalBounds().width / 2
        , WindowMgr::GetInst()->GetWindow().getSize().y / 2
        + m_button2.getGlobalBounds().height / 2);
    m_buttonexit.setPosition(WindowMgr::GetInst()->GetWindow().getSize().x / 2
        - m_buttonexit.getGlobalBounds().width / 2
        , WindowMgr::GetInst()->GetWindow().getSize().y / 2
        + m_buttonexit.getGlobalBounds().height / 2 + m_buttonexit.getGlobalBounds().height);

}
void MenuScene::Update(float _dt)
{
    if (InputMgr::GetInst()->IsSpriteClicked(m_button1, sf::Mouse::Left,
        WindowMgr::GetInst()->GetWindow()))
    {
        SceneMgr::GetInst()->LoadScene("Game_Scene");
    }
}

void MenuScene::Render()
{
    WindowMgr::GetInst()->GetWindow().clear();
    WindowMgr::GetInst()->GetWindow().draw(m_background);
    WindowMgr::GetInst()->GetWindow().draw(m_title);
    WindowMgr::GetInst()->GetWindow().draw(m_button1);
    WindowMgr::GetInst()->GetWindow().draw(m_button2);
    WindowMgr::GetInst()->GetWindow().draw(m_buttonexit);
    WindowMgr::GetInst()->GetWindow().display();

}
