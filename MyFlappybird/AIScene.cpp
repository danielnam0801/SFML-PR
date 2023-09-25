#include "AIScene.h"
#include "define.h"
#include <sstream>
#include <chrono>

AIScene::AIScene(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
	, m_pipeManager(_data)
{
	m_gameData->Window.setSize(sf::Vector2u(SCREEN_WIDTH * 4, SCREEN_HEIGHT * 2));
	m_gameData->Window.setView(sf::View(sf::FloatRect(0, 0, 2 * SCREEN_WIDTH, SCREEN_HEIGHT)));
	m_background.setTexture(m_gameData->Resmgr.GetTexture("AI Background"));
	m_aiText.setFont(m_gameData->Resmgr.GetFont("Flappy Font"));
	m_aiText.setCharacterSize(20);
	m_aiText.setFillColor(sf::Color::White);
	m_aiText.setString("");
	m_aiText.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
}

AIScene::~AIScene()
{
}

void AIScene::Init()
{
	m_vecBird.resize(8);
}

void AIScene::Update(float _dt)
{
	std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());
	bool isStart = true;
	for (AiBird& b : m_vecBird)
	{
		if (!b.GetDead())
		{
			isStart = false;
			break;
		}
	}

	if (!isStart)
	{
		m_pipeManager.Update(_dt, random_engine);
		for (AiBird& b : m_vecBird)
		{
			b.Update(_dt, true, m_pipeManager.GetPipe());
		}
	}


	std::stringstream ss;
	ss << "Score " << m_Score << std::endl;
	m_aiText.setString(ss.str());
}

void AIScene::Render()
{
	m_gameData->Window.clear();
	m_gameData->Window.draw(m_background);
	m_gameData->Window.draw(m_aiText);
	m_pipeManager.Render();
	for (AiBird& b : m_vecBird)
	{
		b.Render(m_gameData->Window);
	}
	m_gameData->Window.display();
}
