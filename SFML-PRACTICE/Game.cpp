#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include<iostream>
#include <sstream>
#define HPBarSizeX 300
#define HPBarSizeY 50

Game::Game()
    : m_IsEndGame(false)
{
    m_iHp = m_maxHp = m_beforeHp = 10;
    m_iScore = 0;

    Initvariable();
    InitWindow();

    std::srand((unsigned int)time(nullptr));
}

Game::~Game() {
    delete m_window;
}

void Game::Update() {
    PollEvent();
    SpawnEnemy();
    UpdateCollision();
    UpdateText();
    m_player->Update(m_window);
}

void Game::Render() {
    m_window->clear();
    for (auto& e : m_vecBall) {
        e.Render(m_window);
    }
    m_player->Render(m_window);
    RenderText(*m_window);
    UpdateGUI();
    m_window->display();
}

void Game::UpdateCollision()
{
    for (size_t i = 0; i < m_vecBall.size(); i++) {
        if (m_vecBall[i].GetCircle().getGlobalBounds().intersects(m_player->GetRect().getGlobalBounds())) {
            switch (m_vecBall[i].GetType())
            {
            case Default:
                break;
            case Score:
                m_iScore += rand() % 5 + 2;
                
                break;
            case Damage:
                m_iHp -= 1;
                break;
            case Heal:
                m_iHp += 1;
                break;
            default:
                break;
            }
            m_vecBall.erase(m_vecBall.begin() + (int)i);
        }
    }
}

void Game::Initvariable() {
    m_window = nullptr;
    m_player = new Player();

    m_fEnemySpawnTimerMax = 10.f;
    m_fEnemySpawnTimer = m_fEnemySpawnTimerMax;
    m_iEnemyMax = 10;

    if (!m_font.loadFromFile("../Res/Font/Rubber-Duck.ttf"))
    {
        std::cout << "Font load Error" << std::endl;
    }
    m_text.setFont(m_font);
    m_text.setCharacterSize(30);
    m_text.setFillColor(sf::Color::White);
    m_text.setString("NONE");

    m_hpbar.setSize(sf::Vector2f((float)HPBarSizeX, (float)HPBarSizeY));
    m_hpbar.setFillColor(sf::Color::Red);
    m_hpbar = m_dynamicBar;
    m_dynamicBar.setFillColor(sf::Color::Blue);

    if (!m_soundbuf[0].loadFromFile("../Res/Sound/Coin.wav")) {
        std::cout << "coin sound load error" << std::endl;
    }
    if (!m_soundbuf[1].loadFromFile("../Res/Sound/Hurt.wav")) {
        std::cout << "Hurt sound load error" << std::endl;
    }
    m_sound[0].setBuffer(m_soundbuf[0]);
    m_sound[1].setBuffer(m_soundbuf[1]);

    if (!m_bgm.openFromFile("../Res/Sound/bgm.mp3")) {
        std::cout << "bgm sound open error" << std::endl;
    }
    m_bgm.play();
    m_bgm.setLoop(true);
}

void Game::InitWindow() {
    m_videomode = { 800, 600 };
    m_window = new sf::RenderWindow(m_videomode, "GAME 2");
    m_window->setFramerateLimit(60);
}

void Game::PollEvent() {
    while (m_window->pollEvent(m_eve)) {
        switch (m_eve.type) {
        case sf::Event::Closed:
            m_window->close();
            break;
        }
    }
}

void Game::SpawnEnemy() {
    if (m_fEnemySpawnTimer < m_fEnemySpawnTimerMax) {
        m_fEnemySpawnTimer += 1.f;
    }
    else {
        if (m_vecBall.size() < m_iEnemyMax) {
            m_vecBall.push_back(Ball(m_window, (EnemyType)(rand() % 3 + 1)));
            m_fEnemySpawnTimer = 0.f;
        }
    }
}

void Game::UpdateEnemy()
{
}

void Game::RenderEnemy()
{
}

void Game::UpdateText() {
    std::stringstream ss;
    ss << std::endl << std::endl << "Score: " << m_iScore << std::endl;
    m_text.setString(ss.str());
    
}

void Game::UpdateGUI()
{
    if (m_hpDecresing) return;
    
    float fPercent = (float)m_iHp / float(m_maxHp);
    if (m_hpbar.getSize().x > 200.f * fPercent) {
        float newSize = m_hpbar.getSize().x - 2.0f;
        m_hpbar.setSize(sf::Vector2f(newSize, m_hpbar.getSize().y));
    }
    else {
        float newSize = m_hpbar.getSize().x + 2.0f;
        m_hpbar.setSize(sf::Vector2f(newSize, m_hpbar.getSize().y));
    }
    m_hpbar.setSize(sf::Vector2f(200.0f * fPercent, m_hpbar.getSize().y));


    //m_hpbar.setSize(sf::Vector2f((float)HPBarSizeX * ((float)m_iHp / (float)m_maxHp), (float)HPBarSizeY));
    //m_dynamicBar.setPosition(m_hpbar.getSize().x,0);
    //
    //m_dynamicRectSizeX = (float)HPBarSizeX * ((float)abs(m_beforeHp - m_iHp) / (float)m_maxHp);
    //m_dynamicBar.setSize(sf::Vector2f(m_dynamicRectSizeX, (float)HPBarSizeY));
    //if (m_beforeHp - m_iHp != 0) {

    //    std::cout << m_beforeHp - m_iHp << std::endl;
    //    std::cout << m_dynamicRectSizeX << std::endl;
    //}

    //if (m_beforeHp - m_iHp >= 1) {//plus
    //    m_dynamicBar.setPosition(sf::Vector2f(m_hpbar.getGlobalBounds().left + m_hpbar.getSize().x, 0));
    //    m_dynamicBar.setScale();
    //}
    //if(m_beforeHp - m_iHp <= -1) {//minus
    //    m_dynamicBar.setPosition(sf::Vector2f(m_hpbar.getGlobalBounds().left + m_hpbar.getSize().x - m_dynamicRectSizeX, 0));
    //    m_dynamicBar.setScale()
    //}
    
    m_hpDecresing = false;
    m_beforeHp = m_iHp;
}

void Game::RenderText(sf::RenderTarget& _target) {
    _target.draw(m_text);
    m_window->draw(m_dynamicBar);
    m_window->draw(m_hpbar);
}