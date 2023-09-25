#include "AiBird.h"
#include "AiPipe.h"
#include "define.h"

AiBird::AiBird()
    : m_IsDead(false)
{
}

void AiBird::Update(float _dt, bool _isMove, std::vector<AiPipe> _pipe)
{
    m_fSpeed += AI_GRAVITY;
    m_birdy += m_fSpeed;

    if (!m_IsDead)
    {
        if (m_fSpeed >= 0 && m_birdy >= 0 && GetGapDiff(_pipe) < -16 || GetGapDiff(_pipe) == 0)
        {
            m_fSpeed += FLIP_SPEED;
        }

        for (AiPipe& p : _pipe)
        {
            //x부분
            if (m_birdx < p.GetX() + BIRD_SIZE * 2 && m_birdx > p.GetX() - BIRD_SIZE)
            {
                //y부분
                if (m_birdy < p.GetY() || m_birdy > p.GetY() + GAP_SIZE - BIRD_SIZE)
                {
                    m_IsDead = true;
                    m_fSpeed = 0;
                }
            }
            else if(m_birdx == p.GetX() + 2 * BIRD_SIZE)
            {
                m_score++;
            }
        }
    }
}

void AiBird::Render(sf::RenderWindow& _window)
{
    sf::Texture tex;
    tex.loadFromFile(AI_BIRD);
    m_birdsprite.setPosition(m_birdx, m_birdy);
    m_birdsprite.setTexture(tex);

    if (!m_IsDead)
        m_birdsprite.setTextureRect(sf::IntRect(BIRD_SIZE * (m_fSpeed <= 0), 0, BIRD_SIZE, BIRD_SIZE));
    else
        m_birdsprite.setTextureRect(sf::IntRect(BIRD_SIZE, BIRD_SIZE, BIRD_SIZE * 2, BIRD_SIZE * 2));
    _window.draw(m_birdsprite);
}

float AiBird::GetGapDiff(std::vector<AiPipe> _pipe)
{
    for (AiPipe& p : _pipe)
    {
        if (m_birdx < p.GetX() + 2 * BIRD_SIZE)
        {
            return p.GetY() + (GAP_SIZE - BIRD_SIZE) / 2 - m_birdy;
        }
    }
    return 0.0f;
}
