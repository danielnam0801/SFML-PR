#include "GameOverScene.h"
#include "GameScene.h"
#include <sstream>
#include <fstream>

GameOverScene::GameOverScene(std::shared_ptr<GameData> _data, int score)
	: m_gamedata(_data)
	, m_Score(score)
{
}

void GameOverScene::Init()
{
	std::ifstream readfile("Output\\Score\\HighScore.txt");
	if (readfile.is_open())
	{
		while (!readfile.eof())
		{
			readfile >> m_highScore;
		}
	}
	readfile.close();

	if (m_highScore < m_Score)
	{
		std::ofstream writeFile("Output\\Score\\HighScore.txt");
		if (writeFile.is_open())
		{
			m_highScore = m_Score;
			writeFile << m_highScore;
		}
		writeFile.close();
	}

	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Main Scene Background"));
	m_title.setTexture(m_gamedata->Resmgr.GetTexture("Game Over Title"));
	m_body.setTexture(m_gamedata->Resmgr.GetTexture("Game Over Body"));
	m_button.setTexture(m_gamedata->Resmgr.GetTexture("PlayButton"));

	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	m_title.setPosition(m_gamedata->Window.getSize().x / 2, m_gamedata->Window.getSize().y / 7 * 2);
	m_body.setOrigin(m_body.getGlobalBounds().width / 2, m_body.getGlobalBounds().height / 2);
	m_body.setPosition(m_gamedata->Window.getSize().x / 2, m_gamedata->Window.getSize().y / 2);
	m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
	m_button.setPosition(m_gamedata->Window.getSize().x / 2, m_gamedata->Window.getSize().y / 5*4 );
	
	m_scoreTxt.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	std::stringstream ss;
	ss << m_Score;
	m_scoreTxt.setString(ss.str());
	m_scoreTxt.setCharacterSize(50);
	m_scoreTxt.setFillColor(sf::Color::White);
	m_scoreTxt.setOrigin(m_scoreTxt.getGlobalBounds().width / 2, m_scoreTxt.getGlobalBounds().height/2);
	m_scoreTxt.setPosition(m_gamedata->Window.getSize().x - m_gamedata->Window.getSize().x / 3.5,
		m_gamedata->Window.getSize().y / 2 - 
		m_body.getGlobalBounds().height /8);
	
	m_highscoreTxt.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	std::stringstream s;
	s << m_highScore;
	m_highscoreTxt.setString(s.str());
	m_highscoreTxt.setCharacterSize(50);
	m_highscoreTxt.setFillColor(sf::Color::White);
	m_highscoreTxt.setOrigin(m_highscoreTxt.getGlobalBounds().width / 2, m_highscoreTxt.getGlobalBounds().height / 2);
	m_highscoreTxt.setPosition(m_gamedata->Window.getSize().x - m_gamedata->Window.getSize().x / 3.7,
		m_gamedata->Window.getSize().y / 2 +
		m_body.getGlobalBounds().height / 5);
}


void GameOverScene::Update(float _dt)
{
	if (m_gamedata->Inputmgr.IsSpliteClicked(m_button, sf::Mouse::Left, m_gamedata->Window))
	{
		m_gamedata->Scenemgr.AddScene(std::make_unique<GameScene>(m_gamedata));
	}
}

void GameOverScene::Render()
{
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.draw(m_title);
	m_gamedata->Window.draw(m_body);
	m_gamedata->Window.draw(m_button);
	m_gamedata->Window.draw(m_scoreTxt);
	m_gamedata->Window.draw(m_highscoreTxt);
	m_gamedata->Window.display();
}
