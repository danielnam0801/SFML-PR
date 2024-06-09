#include "GameScene.h"
#include "Pipe.h"
#include "define.h"
#include "Land.h"
#include "Bird.h"
#include "Flash.h"
#include "GameoverScene.h"
#include<iostream>
#include "Hud.h"
#include<fstream>
GameScene::GameScene(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
	, m_eGameState(GAMESTATE::IDLE)
	, m_Score(0)
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
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Sky Background"));
	m_Sound[(int)SOUNDTYPE::HIT].setBuffer(m_gamedata->Resmgr.GetSoundbuf("Hit Sound"));
	m_Sound[(int)SOUNDTYPE::WING].setBuffer(m_gamedata->Resmgr.GetSoundbuf("Wing Sound"));
	m_Sound[(int)SOUNDTYPE::POINT].setBuffer(m_gamedata->Resmgr.GetSoundbuf("Point Sound"));

	m_pPipe = new Pipe(m_gamedata);
	m_pLand = new Land(m_gamedata);
	m_pBird = new Bird(m_gamedata);
	m_pFlash = new Flash(m_gamedata);
	m_pHud = new Hud(m_gamedata);
}

void GameScene::Update(float _dt)
{
	if (m_gamedata->Inputmgr.IsSpliteClicked(m_background, sf::Mouse::Left, m_gamedata->Window))
	{
		if (m_eGameState != GAMESTATE::GAMEOVER)
		{
			m_eGameState = GAMESTATE::PLAYING;
			m_pBird->Tap();
			m_Sound[(int)SOUNDTYPE::WING].play();
		}
	}
	// 파이프 스폰 기준
	if (m_eGameState != GAMESTATE::GAMEOVER)
	{
		if (m_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
		{
			m_pPipe->SpawnUpdate();
			m_clock.restart();
		}
		m_pPipe->Update(_dt);
		m_pLand->Update(_dt);
		m_pBird->Update(_dt);

		// Land 충돌
		std::vector<sf::Sprite> veclandsprite = m_pLand->GetSprite();
		for (size_t i = 0; i < veclandsprite.size(); ++i)
		{
			if (m_collision.IsSpriteCollision(m_pBird->GetSprite(),0.6f, veclandsprite[i],1.0f))
			{
				m_eGameState = GAMESTATE::GAMEOVER;
				m_clock.restart();
				m_Sound[(int)SOUNDTYPE::HIT].play();
			}
		}
		// Pipe 충돌
		std::vector<sf::Sprite> vecpipesprite = m_pPipe->GetSprite();
		for (size_t i = 0; i < vecpipesprite.size(); ++i)
		{
			if (m_collision.IsSpriteCollision(m_pBird->GetSprite(),0.6f, vecpipesprite[i],1.0f))
			{
				m_eGameState = GAMESTATE::GAMEOVER;
				m_clock.restart();
				m_Sound[(int)SOUNDTYPE::HIT].play();

			}
		}
		std::ifstream readFile("Output\\Score\\HighScore.txt");
		readFile >> m_temphighscore;
		// ScorePipe 충돌
		std::vector<sf::Sprite>& vecScoresprite = m_pPipe->GetScoreSprite();
		for (size_t i = 0; i < vecScoresprite.size();)
		{
			if (m_collision.IsSpriteCollision(m_pBird->GetSprite(), 0.6f, vecScoresprite[i], 1.0f))
			{
				m_Score++;
				m_Sound[(int)SOUNDTYPE::POINT].play();
				//std::cout << m_Score << std::endl;
				m_pHud->Update(m_Score);
				if (m_Score > m_temphighscore)
					m_isHigh = true;
				vecScoresprite.erase(vecScoresprite.begin() + i);
			}
			else
				++i;
		}
		if (m_isHigh)
			m_pHud->HighUpdate(_dt);

	}
	m_pBird->Animate(_dt);
	// 요다 비교법
	if (GAMESTATE::GAMEOVER == m_eGameState)
	{
		m_pFlash->Update(_dt);
		//m_gamedata->Scenemgr.AddScene(std::make_unique<GameoverScene>(m_gamedata));
		if(m_clock.getElapsedTime().asSeconds() > 1.5f)
			m_gamedata->Scenemgr.AddScene(std::make_unique<GameoverScene>(m_gamedata, m_Score));
	}
}

void GameScene::Render()
{
	// sfml : clear -> draw -> display
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_pPipe->Render();
	m_pLand->Render();
	m_pBird->Render();
	m_pFlash->Render();
	m_pHud->Render();
	if (m_isHigh)
		m_pHud->HighRender();
	m_gamedata->Window.display();
}
