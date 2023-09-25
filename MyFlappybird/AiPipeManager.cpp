#include "AiPipeManager.h"
#include "define.h"
#include "AiPipe.h"

AiPipeManager::AiPipeManager(std::shared_ptr<GameData> _data)
	: m_gameData(_data)
	, m_Ydistribution (PIPE_INDENT, GROUND_Y - GAP_SIZE - PIPE_INDENT)
	, m_timer(TIMER_DURATION)
{
}

void AiPipeManager::Update(float _dt, std::mt19937_64& _randomEngine)
{
	//� Ÿ�̸Ӹ� �������� �ϴµ� �� Ÿ�̸Ӱ� �Ǹ���
	//���� ����ִ� ����(ai������) push_back
	if (m_timer == 0)
	{
		m_timer = TIMER_DURATION;
		m_vecPipe.push_back(AiPipe(m_gameData, SCREEN_WIDTH, m_Ydistribution(_randomEngine)));
	}
	m_timer--;
	//ai���������� ������Ʈ
	for (AiPipe& p : m_vecPipe)
	{
		p.Update(_dt);
	}

	std::vector<AiPipe>::iterator iter = m_vecPipe.begin();
	for (; iter != m_vecPipe.end(); )
	{
		if (iter->IsGone())
		{
			iter = m_vecPipe.erase(iter);
		}
		else
			++iter;
	}
	//�������� �������� �Ѵٸ� erase
}

void AiPipeManager::Render()
{
	for (AiPipe& p : m_vecPipe)
		p.Render();
}

void AiPipeManager::Reset()
{
	m_vecPipe.clear();
	m_timer = TIMER_DURATION;
}
