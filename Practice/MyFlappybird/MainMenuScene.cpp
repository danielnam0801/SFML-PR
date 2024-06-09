#include "MainMenuScene.h"
#include "GameScene.h"
#include "AiScene.h"
MainMenuScene::MainMenuScene(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
{
}

void MainMenuScene::Init()
{
	// 세팅을하고 
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Sky Background"));
	m_playbutton.setTexture(m_gamedata->Resmgr.GetTexture("Play Button"));
	m_title.setTexture(m_gamedata->Resmgr.GetTexture("Game Title"));

	m_title.setPosition((m_gamedata->Window.getSize().x / 2) - m_title.getGlobalBounds().width / 2
		, m_title.getGlobalBounds().height / 2 );

	m_playbutton.setPosition((m_gamedata->Window.getSize().x / 2) - m_playbutton.getGlobalBounds().width / 2
	, m_gamedata->Window.getSize().y / 2 - m_playbutton.getGlobalBounds().height / 2);
}

void MainMenuScene::Update(float _dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_gamedata->Scenemgr.AddScene(std::make_unique<AiScene>(m_gamedata));
	}
	// 클릭하면 Game Scene으로 넘어가게.
	if (m_gamedata->Inputmgr.IsSpliteClicked(m_playbutton,sf::Mouse::Left, m_gamedata->Window))
	{
		m_gamedata->Scenemgr.AddScene(std::make_unique<GameScene>(m_gamedata));
	}
}

void MainMenuScene::Render()
{
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.draw(m_playbutton);
	m_gamedata->Window.draw(m_title);
	m_gamedata->Window.display();

}
