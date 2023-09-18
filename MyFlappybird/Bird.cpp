#include "Bird.h"

#include "Bird.h"
#include "define.h"
Bird::Bird(std::shared_ptr<GameData> _data)
    : m_gameData(_data)
    , m_animiter(0)
    , m_anitime(0)
    , m_rotate(0.f)

{
    m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 1"));
    m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 2"));
    m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 3"));
    m_vecanim.push_back(m_gameData->Resmgr.GetTexture("Bird 4"));
    m_birdsprite.setTexture(m_vecanim[m_animiter]);
    m_birdsprite.setPosition(m_gameData->Window.getSize().x / 4 - m_birdsprite.getGlobalBounds().width / 2
        , m_gameData->Window.getSize().y / 2 - m_birdsprite.getGlobalBounds().height / 2);
    m_ebirdState = BIRDSTATE::IDLE;
    m_birdsprite.setOrigin(m_birdsprite.getGlobalBounds().width/2
                    , m_birdsprite.getGlobalBounds().height/2);
}

void Bird::Update(float _dt)
{
    // 나는거랑 떨어지는거랑 enum class 상태값 분류해서
    if (m_ebirdState == BIRDSTATE::FALL)
    {
        m_birdsprite.move(0, GRAVITY * _dt);
        m_rotate += ROTATE_SPEED * _dt;
        if (m_rotate > 80.0f)
        {
            m_rotate = 80.0f;
        }
        m_birdsprite.setRotation(m_rotate);
    }
    else if (m_ebirdState == BIRDSTATE::FLY)
    {
        m_birdsprite.move(0, -FLYING_SPEED * _dt);
        m_rotate -= ROTATE_SPEED * _dt;
        if (m_rotate < -80.0f)
        {
            m_rotate = -80.0f;
        }
        m_birdsprite.setRotation(m_rotate);
    }
    if (m_movementclock.getElapsedTime().asSeconds() > FLYING_DURATION)
    {
        m_movementclock.restart();
        m_ebirdState = BIRDSTATE::FALL;
    }
}

void Bird::Animate(float _dt)
{
    m_anitime += _dt;
    if (m_anitime >= BIRD_ANIMATION_DURATION / m_vecanim.size()) // 시간 관련 기준.
    {
        m_anitime = 0.0f; // m_clock.restart();
        if (m_animiter < m_vecanim.size() - 1)
            m_animiter++;
        else
            m_animiter = 0;

    }
    m_birdsprite.setTexture(m_vecanim[m_animiter]);
}

void Bird::Tap()
{
    m_movementclock.restart();
    m_ebirdState = BIRDSTATE::FLY;
}

void Bird::Render()
{
    m_gameData->Window.draw(m_birdsprite);
}