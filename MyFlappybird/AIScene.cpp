#include "AIScene.h"
#include "define.h"
#include <sstream>
#include <chrono>

std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());
AIScene::AIScene(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
	, m_pipeManager(_data)
	, m_vecBird {0}
	, m_generation(1)
	, m_gameSpeed(1)
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
	for (AiBird& b : m_vecBird)
		b.Setting_Weight(random_engine);
}

void AIScene::Update(float _dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_gameSpeed *= 2;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_gameSpeed > 1) m_gameSpeed /= 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_gameSpeed = 1;
	}

	for (int i = 0; i < m_gameSpeed; i++)
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
			m_pipeManager.Update(_dt, random_engine);
			for (AiBird& b : m_vecBird)
			{
				b.Update(_dt, true, m_pipeManager.GetPipe());
			}
		}
		else
		{
			m_generation++;

			std::sort(m_vecBird.begin(), m_vecBird.end(), std::greater<>());
			//CROSSOVER
			for (auto iter = m_vecBird.begin() + 2; iter != m_vecBird.end(); ++iter)
			{
				iter->CrossOver(random_engine, m_vecBird[0].GetWeight(), m_vecBird[1].GetWeight());
			}

			for (AiBird& b : m_vecBird)
				b.Reset();
			m_pipeManager.Reset();
		}

		int max_score = std::max_element(m_vecBird.begin(), m_vecBird.end())->GetScore();
		if (m_Score < max_score)
		{
			m_Score = max_score;
		}

		std::stringstream ss;
		ss << "Score " << m_Score << std::endl;
		ss << "Generation " << m_generation << std::endl;
		ss << "GameSpeed " << m_gameSpeed << std::endl;
		m_aiText.setString(ss.str());
	}
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
