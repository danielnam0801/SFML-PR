#include "AiBird.h"
#include "define.h"
AiBird::AiBird()
	: m_weight(2)
	, m_nodeDistribution(-1,1)
	, m_mutationDistribution(0, MUTATION_PROBABILITY -1)
	, m_neuralnetwork(3)
	//: m_IsDead(false)
	//, m_fSpeed(0.f)
	//, m_birdx(BIRD_START_X)
	//, m_birdy(GROUND_Y - BIRD_SIZE / 2)
	//, m_score(0)
{
	Reset();
}

void AiBird::Update(float _dt, bool _isMove, std::vector<AiPipe> _pipe)
{
	m_fSpeed += AI_GRAVITY;
	m_birdy += m_fSpeed;
	if (!m_IsDead)
	{
											// ?? 언제? 
		// My algorithm
		//if (m_fSpeed >= 0 && m_birdy >= 0 && GetGapDiff(_pipe) < -16 || GetGapDiff(_pipe) == 0)
		
		// AI버전
		if (m_fSpeed >= 0 && m_birdy >= 0 && DoArtificial_Intelligence(_pipe))
		{
			m_fSpeed = FLIP_SPEED;
		}

		for (AiPipe& p : _pipe)
		{
			// 죽는 상황이 아니다.
			// x부분
			if (m_birdx < p.GetX() + BIRD_SIZE * 2 && m_birdx > p.GetX() - BIRD_SIZE)
			{
				// y부분
					// 새가 파이프보다 위여서 죽음 혹은 점프하면 죽는상황
				if (m_birdy < p.GetY() || m_birdy > p.GetY() + GAP_SIZE - BIRD_SIZE)
				{
					m_IsDead = true;
					m_fSpeed = 0;
				}
			}
			// 살아있는거지?
			else if (m_birdx == p.GetX() + 2 * BIRD_SIZE)
				m_score++;
		}
		m_fitness += BIRD_SPEED;
	}
}

void AiBird::Render(sf::RenderWindow& _window)
{
	sf::Texture tex;
	tex.loadFromFile(AI_BIRD);
	m_birdsprite.setPosition(m_birdx, round(m_birdy));
	m_birdsprite.setTexture(tex);

	if (!m_IsDead)
		m_birdsprite.setTextureRect(sf::IntRect(BIRD_SIZE * (0 >= m_fSpeed), 0,BIRD_SIZE, BIRD_SIZE));
	else
		m_birdsprite.setTextureRect(sf::IntRect(BIRD_SIZE, BIRD_SIZE, BIRD_SIZE*2, BIRD_SIZE*2));
	_window.draw(m_birdsprite);
}

float AiBird::GetGapDiff(std::vector<AiPipe> _pipe)
{
	for (AiPipe& p : _pipe)
	{
		// 한 이쯤 되면? 갭 계산 해보자.
		if (m_birdx < p.GetX() + 2 * BIRD_SIZE)
		{						// 64 - 16 
			return p.GetY() + (GAP_SIZE - BIRD_SIZE) / 2 - m_birdy;
			//return p.GetY() + GAP_SIZE - BIRD_SIZE - m_birdy;
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
	m_weight[0].resize(TOTAL_INPUT_NODE,std::vector<float>(TOTAL_HIDDEN_NODE));
	m_weight[1].resize(TOTAL_HIDDEN_NODE, std::vector<float>(TOTAL_OUTPUT_NODE));

	// weight 입력.
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

bool AiBird::DoArtificial_Intelligence(std::vector<AiPipe> _pipe)
{
	m_neuralnetwork[0].resize(TOTAL_INPUT_NODE);
	m_neuralnetwork[1].resize(TOTAL_HIDDEN_NODE);
	m_neuralnetwork[2].resize(TOTAL_OUTPUT_NODE);
	
	// input
	m_neuralnetwork[0][0] = m_fSpeed; // 스피드
	m_neuralnetwork[0][1] = GetGapDiff(_pipe); // 스피드
	for (AiPipe& p : _pipe)
	{
		if (m_birdx < p.GetX() + 2 * BIRD_SIZE)
		{
			m_neuralnetwork[0][2] = p.GetDir();
			break;
		}
	}

	//// i는 0아니면 1
	//for (size_t i = 0; i < m_neuralnetwork.size() - 1; i++)
	//{
	//	// j는 히든 노드쪽과 출력 노드쪽
	//	for (size_t j = 0; j < m_neuralnetwork[i + 1].size(); j++)
	//	{
	//		// k는 입력노드쪽과 히든 노드쪽
	//		for (size_t k = 0; k < m_neuralnetwork[i].size(); k++)
	//		{
	//			m_neuralnetwork[i + 1][j] += m_neuralnetwork[i][k] * m_weight[i][k][j];
	//		}

	//		// 활성화 함수.
	//		if (m_neuralnetwork[i + 1][j] <= 0)
	//		{
	//			m_neuralnetwork[i + 1][j] = pow<float>(2, m_neuralnetwork[i + 1][j]) -1;
	//		}
	//		else
	//		{
	//			m_neuralnetwork[i + 1][j] = 1 - pow<float>(2, -m_neuralnetwork[i + 1][j]);
	//		}
	//	}
	//}
	// 여기서 행렬?
	for (size_t a = 0; a < m_neuralnetwork.size() - 1; a++)
	{
		for (size_t b = 0; b < m_neuralnetwork[1 + a].size(); b++)
		{
			for (size_t c = 0; c < m_neuralnetwork[a].size(); c++)
			{
				// [1][1] += [0][0] * weight[0][0][0]
				m_neuralnetwork[1 + a][b] += m_neuralnetwork[a][c] * m_weight[a][c][b];
			}

			if (0 >= m_neuralnetwork[1 + a][b])
			{
				//				neural_network[1 + a][b] = pow<float>(M_E, neural_network[1 + a][b]) - 1;
				m_neuralnetwork[1 + a][b] = pow<float>(2, m_neuralnetwork[1 + a][b]) - 1;
			}
			else
			{
				m_neuralnetwork[1 + a][b] = 1 - pow<float>(2, -m_neuralnetwork[1 + a][b]);
			}
		}
	}
	return m_neuralnetwork[2][0] >= 0;
}

void AiBird::CrossOver(std::mt19937_64& _randomengine, std::vector<std::vector<std::vector<float>>> _bird1, std::vector<std::vector<std::vector<float>>> _bird2)
{
	for (size_t i = 0; i < m_weight.size(); i++)
	{
		for (size_t j = 0; j < m_weight[i].size(); j++)
		{
			for (size_t k = 0; k < m_weight[i][j].size(); k++)
			{
				if (rand() % 2 == 0)
				{
					m_weight[i][j][k] = _bird1[i][j][k];
				}
				else
				{
					m_weight[i][j][k] = _bird2[i][j][k];
				}
				// 돌연변이 확률 mutation;
				if (m_mutationDistribution(_randomengine) == 0)
				{
					m_weight[i][j][k] = m_nodeDistribution(_randomengine);
				}
			}
		}
	}
}


