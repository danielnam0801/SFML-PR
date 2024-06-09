#include "AiScene.h"
#include "define.h"
#include <sstream>
#include <chrono>
#include<algorithm>
std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

AiScene::AiScene(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
	, m_pipemgr(_data)
	, m_vecBird{}
	, m_generation(1)
	, m_gamespeed(1)
{
	m_gamedata->Window.setSize(sf::Vector2u(SCREEN_WIDTH * 4, SCREEN_HEIGHT*2));
	m_gamedata->Window.setView(sf::View(sf::FloatRect(0,0, 2*SCREEN_WIDTH, SCREEN_HEIGHT)));
	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Ai Background"));
	m_aitext.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	m_aitext.setCharacterSize(20);
	m_aitext.setFillColor(sf::Color::White);
	m_aitext.setString("");
	m_aitext.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
}

AiScene::~AiScene()
{
}

void AiScene::Init()
{
	m_vecBird.resize(8);
	for (AiBird& b : m_vecBird)
		b.Setting_Weight(random_engine);
}

void AiScene::Update(float _dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_gamespeed *= 2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_gamespeed > 1)
			m_gamespeed /= 2;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		m_gamespeed = 1;
	for (int i = 0; i < m_gamespeed; i++)
	{
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
			m_pipemgr.Update(_dt, random_engine);
			for (AiBird& b : m_vecBird)
			{
				b.Update(_dt, true, m_pipemgr.GetPipe());
			}
		}
		else // Á×Àº ½ÃÁ¡.
		{
			m_generation++;

			std::sort(m_vecBird.begin(), m_vecBird.end(), std::greater<>());
			// CrossOver
			for (auto iter = m_vecBird.begin() + 2; iter != m_vecBird.end(); ++iter)
			{
				iter->CrossOver(random_engine, m_vecBird[0].GetWeight(), m_vecBird[1].GetWeight());
			}

			for (AiBird& b : m_vecBird)
				b.Reset();
			m_pipemgr.Reset();
		}
		int max_score = std::max_element(m_vecBird.begin(), m_vecBird.end())->GetScore();
		if (m_Score < max_score)
		{
			m_Score = max_score;
		}

		std::stringstream ss;
		ss << "Score: " << m_Score << std::endl;
		ss << "Generation: " << m_generation << std::endl;
		ss << "GameSpeed: " << m_gamespeed << std::endl;
		m_aitext.setString(ss.str());
	}
	
}

void AiScene::Render()
{
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_pipemgr.Render();
	for (AiBird& b : m_vecBird)
		b.Render(m_gamedata->Window);
	m_gamedata->Window.draw(m_aitext);
	m_gamedata->Window.display();
}
