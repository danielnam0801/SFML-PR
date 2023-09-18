#include "GameScene.h"
#include "Pipe.h"
#include "Bird.h"
#include "Land.h"
#include "Flash.h"
#include "GameOverScene.h"
#include <sstream>
#include <iostream>


GameScene::GameScene(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
	, m_gameState(GAMESTATE::IDLE)
	, m_iScore(0)
{
	
}

GameScene::~GameScene()
{
	delete m_pPipe;
	delete m_pLand;
	delete m_pBird;
	delete m_pFlash;
}

void GameScene::Init()
{
	m_background.setTexture(m_gameData->Resmgr.GetTexture("Main Scene Background"));
	m_text.setFont(m_gameData->Resmgr.GetFont("Font Score"));
	m_text.setCharacterSize(50);
	m_text.setPosition(m_gameData->Window.getSize().x - m_text.getGlobalBounds().width / 2
						, m_gameData->Window.getSize().y - m_text.getGlobalBounds().height/2);
	m_pPipe = new Pipe(m_gameData);
	m_pLand = new Land(m_gameData);
	m_pBird = new Bird(m_gameData);
	m_pFlash = new Flash(m_gameData);
	m_pPipe->m_landHeight = m_pLand->landHeight;
}

void GameScene::Update(float _dt)
{
	if (m_gameData->Inputmgr.IsSpliteClicked(m_background, sf::Mouse::Left, m_gameData->Window))
	{
		if (m_gameState != GAMESTATE::GAMEOVER)
		{
			m_pBird->Tap();
			m_gameState = GAMESTATE::PLAYIMG;
		}
	}

	if (m_gameState == GAMESTATE::PLAYIMG)
	{
		m_pPipe->Update(_dt);
		m_pLand->Update(_dt);
		m_pBird->Update(_dt);
	}

	std::vector<sf::Sprite> veclandsprite = m_pLand->GetSprite();
	for (size_t i = 0; i < veclandsprite.size(); i++)
	{
		if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, veclandsprite[i], 1.0f)) {
			m_gameState = GAMESTATE::GAMEOVER;
		}
	}
	std::vector<sf::Sprite> vecpipesprite = m_pPipe->GetSprite();
	for (size_t i = 0; i < vecpipesprite.size(); i++)
	{
		if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, vecpipesprite[i], 1.0f)) {
			m_gameState = GAMESTATE::GAMEOVER;
		}
	}
	
	std::vector<sf::Sprite> vecscorepipesprite = m_pPipe->GetScorePipeSprite();
	for (size_t i = 0; i < vecpipesprite.size(); i++)
	{
		if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, vecpipesprite[i], 1.0f)) {
			m_iScore++;
		}
	}
	m_pBird->Animate(_dt);
	
	if (m_gameState == GAMESTATE::GAMEOVER) {
		m_pFlash->Update(_dt);
		m_gameData->Scenemgr.AddScene(std::make_unique<GameOverScene>(m_gameData));
	}
}

void GameScene::Render()
{
	//sfml : clear -> draw -> display
	m_gameData->Window.clear();
	RenderScore();
	m_gameData->Window.draw(m_background);
	m_pPipe->Render();
	m_pLand->Render();
	m_pBird->Render();
	m_pFlash->Render();
	m_gameData->Window.display();
}

void GameScene::RenderScore()
{
	std::stringstream ss;
	ss << m_iScore << std::endl;
	std::cout << m_iScore << std::endl;
	m_text.setString(ss.str());
	m_gameData->Window.draw(m_text);
}
