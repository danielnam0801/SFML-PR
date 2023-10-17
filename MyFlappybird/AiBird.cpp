#include "AiBird.h"
#include "AiPipe.h"
#include "define.h"

AiBird::AiBird()
    : m_weight(2)
    , m_nodeDistribution(-1, 1)
    , m_neuralnetwork(3)
    , m_mutationDistribution(0, MUTATION_PROBABILITY - 1)
{
    Reset();
}

void AiBird::Update(float _dt, bool _isMove, std::vector<AiPipe> _pipe)
{
    m_fSpeed += AI_GRAVITY;
    m_birdy += m_fSpeed;

    if (!m_IsDead)
    {
        //My algorithm
        //if (m_fSpeed >= 0 && m_birdy >= 0 && GetGapDiff(_pipe) < -16 || GetGapDiff(_pipe) == 0)
        if(m_fSpeed >= 0 && m_birdy >= 0 && DoArtifcial_Intelligence(_pipe))
        {
            m_fSpeed = FLIP_SPEED;
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
        m_fitness += BIRD_SPEED;
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

void AiBird::Reset()
{
    m_IsDead = false;
    m_birdx = BIRD_START_X;
    m_birdy = (GROUND_Y - BIRD_SIZE) / 2;
    m_fSpeed = 0.f;
    m_score = 0;
    m_fitness = 0;
}

void AiBird::Setting_Weight(std::mt19937_64& _randomengine)
{
    // weight 초기화
    m_weight[0].resize(TOTAL_INPUT_NODE, std::vector<float>(TOTAL_HIDDEN_NODE));
    m_weight[1].resize(TOTAL_HIDDEN_NODE, std::vector<float>(TOTAL_OUTPUT_NODE));

    // weight 입력
    for (std::vector<std::vector<float>>& layer : m_weight)
    {
        for (std::vector<float>& node : layer)
        {
            for (float& curnode : node)
            {
                curnode = m_nodeDistribution(_randomengine);
            }
        }
    }
    
}

bool AiBird::DoArtifcial_Intelligence(std::vector<AiPipe> _pipe)
{
    m_neuralnetwork[0].resize(TOTAL_INPUT_NODE);
    m_neuralnetwork[1].resize(TOTAL_HIDDEN_NODE);
    m_neuralnetwork[2].resize(TOTAL_OUTPUT_NODE);

    m_neuralnetwork[0][0] = m_fSpeed;
    m_neuralnetwork[0][1] = GetGapDiff(_pipe);
    for (AiPipe& p : _pipe)
    {
        if (m_birdx < p.GetX() + 2 * BIRD_SIZE)
        {
            m_neuralnetwork[0][2] = p.GetDir();
            break;
        }
    }

    for (size_t i = 0; i < m_neuralnetwork.size() - 1; i++) 
    {
        for (size_t j = 0; j < m_neuralnetwork[i + 1].size(); j++)
        {
            for (size_t k = 0; k < m_neuralnetwork[i].size(); k++)
            {
                m_neuralnetwork[i + 1][j] += m_neuralnetwork[i][k] * m_weight[i][k][j];
            }

            //활성화 함수
            if (m_neuralnetwork[i + 1][j] >= 0)
            {
                m_neuralnetwork[i + 1][j] = pow<float>(2, m_neuralnetwork[i + 1][j]) - 1;
            }
            else
            {
                m_neuralnetwork[i + 1][j] = 1- pow<float>(2, -m_neuralnetwork[i + 1][j]);
            }
        }
    }
    return m_neuralnetwork[2][0] >= 0;
}

void AiBird::CrossOver(std::mt19937_64& _randomengine
    ,std::vector<std::vector<std::vector<float>>> bird1
    ,std::vector<std::vector<std::vector<float>>> bird2)
{
    for (size_t i = 0; i < m_weight.size(); i++)
    {
        for (size_t j = 0; j < m_weight[i].size(); j++)
        {
            for (size_t k = 0; k < m_weight[i][j].size(); k++)
            {
                if (rand() % 2 == 0)
                {
                    m_weight[i][j][k] = bird1[i][j][k];
                }
                else 
                {
                    m_weight[i][j][k] = bird2[i][j][k];
                }
                if (m_mutationDistribution(_randomengine) == 0)
                {
                    m_weight[i][j][k] = m_nodeDistribution(_randomengine);
                }
            }
        }
    }
}
