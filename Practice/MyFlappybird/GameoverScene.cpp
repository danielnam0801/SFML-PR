#include "GameoverScene.h"
#include "GameScene.h"
#include <sstream>
#include <fstream>
GameoverScene::GameoverScene(std::shared_ptr<GameData> _data, int _score)
	: m_gamedata(_data)
	, m_Score(_score)
{
}

void GameoverScene::Init()
{
	// 파일 입출력. 
	std::ifstream readfile("Output\\Score\\HighScore.txt");
	if (readfile.is_open())
	{
		while (!readfile.eof())
			readfile >> m_highScore;
	}
	readfile.close();
	
	if (m_Score > m_highScore)
	{
		std::ofstream writeFile("Output\\Score\\HighScore.txt");
		if (writeFile.is_open())
		{
			m_highScore = m_Score;
			writeFile << m_highScore;
		}
		writeFile.close();
	}

	m_background.setTexture(m_gamedata->Resmgr.GetTexture("Sky Background"));
	m_title.setTexture(m_gamedata->Resmgr.GetTexture("Game Over Title"));
	m_body.setTexture(m_gamedata->Resmgr.GetTexture("Game Over Body"));
	m_button.setTexture(m_gamedata->Resmgr.GetTexture("Play Button"));

	m_body.setOrigin(m_body.getGlobalBounds().width / 2, m_body.getGlobalBounds().height / 2);
	m_body.setPosition(m_gamedata->Window.getSize().x /2,m_gamedata->Window.getSize().y / 2);
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	m_title.setPosition(m_gamedata->Window.getSize().x /2, m_gamedata->Window.getSize().y / 5);
	m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
	m_button.setPosition(m_gamedata->Window.getSize().x /2, m_gamedata->Window.getSize().y / 6 * 5);

	m_scoreText.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	std::stringstream ss;
	ss << m_Score;
	m_scoreText.setString(ss.str());
//	m_scoreText.setString(std::to_string(m_Score));
	m_scoreText.setCharacterSize(50);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setOrigin(m_scoreText.getGlobalBounds().width / 2
	, m_scoreText.getGlobalBounds().height / 2);
	m_scoreText.setPosition(m_gamedata->Window.getSize().x - 
		m_gamedata->Window.getSize().x / 3.5
	,m_gamedata->Window.getSize().y / 2 - 
		m_body.getGlobalBounds().height / 8);

	m_highscoreText.setFont(m_gamedata->Resmgr.GetFont("Flappy Font"));
	m_highscoreText.setString(std::to_string(m_highScore));
	m_highscoreText.setCharacterSize(50);
	m_highscoreText.setFillColor(sf::Color::White);
	m_highscoreText.setOutlineColor(sf::Color::Black);
	m_highscoreText.setOutlineThickness(2);
	m_highscoreText.setOrigin(m_highscoreText.getGlobalBounds().width / 2
		, m_highscoreText.getGlobalBounds().height / 2);
	m_highscoreText.setPosition(m_gamedata->Window.getSize().x -
		m_gamedata->Window.getSize().x / 3.7,
		m_gamedata->Window.getSize().y / 2 + m_body.getGlobalBounds().height / 5);
}

void GameoverScene::Update(float _dt)
{
	if (m_gamedata->Inputmgr.IsSpliteClicked(m_button, sf::Mouse::Left, m_gamedata->Window))
	{
		m_gamedata->Scenemgr.AddScene(std::make_unique<GameScene>(m_gamedata));
	}
}

void GameoverScene::Render()
{
	m_gamedata->Window.clear();
	m_gamedata->Window.draw(m_background);
	m_gamedata->Window.draw(m_title);
	m_gamedata->Window.draw(m_body);
	m_gamedata->Window.draw(m_button);
	m_gamedata->Window.draw(m_scoreText);
	m_gamedata->Window.draw(m_highscoreText);
	m_gamedata->Window.display();
}
