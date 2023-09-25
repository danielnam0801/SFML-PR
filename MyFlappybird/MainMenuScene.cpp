#include "MainMenuScene.h"
#include "GameScene.h" 
#include "AIScene.h"

MainMenuScene::MainMenuScene(std::shared_ptr<GameData> _data)
	:m_gamedata(_data)
{
}

void MainMenuScene::Init()
{
	m_title.setTexture(m_gamedata->Resmgr.GetTexture("Title"));
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Main Scene Background"));
	m_playButton.setTexture(m_gamedata->Resmgr.GetTexture("PlayButton"));

	m_title.setPosition(m_gamedata->Window.getSize().x / 2 - m_title.getGlobalBounds().getSize().x/2, 70);
	m_playButton.setPosition(m_gamedata->Window.getSize().x / 2 - m_playButton.getGlobalBounds().getSize().x / 2, 400);
}

void MainMenuScene::Update(float _dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_gamedata->Scenemgr.AddScene(std::make_unique<AIScene>(m_gamedata));
	}
	if (m_gamedata->Inputmgr.IsSpliteClicked(m_playButton, sf::Mouse::Left, m_gamedata->Window)) 
	{
		m_gamedata->Scenemgr.AddScene(std::make_unique<GameScene>(m_gamedata));
	}
}

void MainMenuScene::Render()
{
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.draw(m_playButton);
	m_gamedata->Window.draw(m_title);
	m_gamedata->Window.display();
}
