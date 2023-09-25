#include "GameScene.h"
#include "Pipe.h"
#include "Bird.h"
#include "Land.h"
#include "Flash.h"
#include "Hud.h"
#include "GameOverScene.h"
#include <iostream>
#include <fstream>


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
	delete m_pHud;
}

void GameScene::Init()
{
	m_background.setTexture(m_gameData->Resmgr.GetTexture("Main Scene Background"));
	m_Sound[(int)SOUNDTYPE::HIT].setBuffer(m_gameData->Resmgr.GetSoundbuf("Hit Sound"));
	m_Sound[(int)SOUNDTYPE::WING].setBuffer(m_gameData->Resmgr.GetSoundbuf("Wing Sound"));
	m_Sound[(int)SOUNDTYPE::POINT].setBuffer(m_gameData->Resmgr.GetSoundbuf("Point Sound"));

	m_pPipe = new Pipe(m_gameData);
	m_pLand = new Land(m_gameData);
	m_pBird = new Bird(m_gameData);
	m_pFlash = new Flash(m_gameData);
	m_pHud = new Hud(m_gameData);
	m_pPipe->m_landHeight = m_pLand->landHeight;
}

void GameScene::Update(float _dt)
{
	if (m_gameData->Inputmgr.IsSpliteClicked(m_background, sf::Mouse::Left, m_gameData->Window))
	{
		if (m_gameState != GAMESTATE::GAMEOVER)
		{
			m_pBird->Tap();
			m_Sound[(int)SOUNDTYPE::WING].play();
			m_gameState = GAMESTATE::PLAYIMG;
		}
	}

	if (m_gameState == GAMESTATE::PLAYIMG)
	{
		m_pPipe->Update(_dt);
		m_pLand->Update(_dt);
		m_pBird->Update(_dt);
		if (ishighScore)
		{
			m_pHud->HighUpdate(_dt);
		}
	}

	std::vector<sf::Sprite> veclandsprite = m_pLand->GetSprite();
	for (size_t i = 0; i < veclandsprite.size(); i++)
	{
		if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, veclandsprite[i], 1.0f)) {
			if (m_gameState != GAMESTATE::GAMEOVER)
			{
				m_Sound[(int)SOUNDTYPE::HIT].play();
				m_clock.restart();
			}
			m_gameState = GAMESTATE::GAMEOVER;
		}
	}

	std::vector<sf::Sprite> vecpipesprite = m_pPipe->GetSprite();
	for (size_t i = 0; i < vecpipesprite.size(); i++)
	{
		if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, vecpipesprite[i], 1.0f)) {
			if (m_gameState != GAMESTATE::GAMEOVER)
			{
				m_Sound[(int)SOUNDTYPE::HIT].play();
				m_clock.restart();
			}
			m_gameState = GAMESTATE::GAMEOVER;
		}
	}
	
	std::vector<sf::Sprite>& vecscorepipesprite = m_pPipe->GetScorePipeSprite();
	for (size_t i = 0; i < vecscorepipesprite.size(); )
	{
		if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, vecscorepipesprite[i], 1.0f)) {
			m_iScore++;
			m_Sound[(int)SOUNDTYPE::POINT].play();
			int m_highScore = 0;
			std::ifstream readfile("Output\\Score\\HighScore.txt");
			readfile >> m_highScore;
		
			if (m_iScore > m_highScore)
			{
				ishighScore = true;
			}

			m_pHud->Update(m_iScore);
			vecscorepipesprite.erase(vecscorepipesprite.begin() + i);
		}
		else {
			++i;
		}
	}
	

	m_pBird->Animate(_dt);
	
	if (m_gameState == GAMESTATE::GAMEOVER) {
		m_pFlash->Update(_dt);
		if(m_clock.getElapsedTime().asSeconds() > 1.5f)
			m_gameData->Scenemgr.AddScene(std::make_unique<GameOverScene>(m_gameData, m_iScore));
	}

}

void GameScene::Render()
{
	//sfml : clear -> draw -> display
	m_gameData->Window.clear();
	m_gameData->Window.draw(m_background);
	m_pPipe->Render();
	m_pLand->Render();
	m_pBird->Render();
	m_pFlash->Render();
	m_pHud->Render();
	if (ishighScore) m_pHud->HighRender();
	m_gameData->Window.display();
}