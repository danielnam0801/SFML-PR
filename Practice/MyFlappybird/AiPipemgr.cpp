#include "AiPipemgr.h"
#include "define.h"
#include "AiPipe.h"
AiPipemgr::AiPipemgr(std::shared_ptr<GameData> _data)
	: m_gamedata(_data)
	, m_Ydistribution(PIPE_INDENT, GROUND_Y - GAP_SIZE - PIPE_INDENT)
	, m_timer(TIMER_DURATION)
{
}

void AiPipemgr::Reset()
{
	m_vecPipe.clear();
	m_timer = TIMER_DURATION;
}

void AiPipemgr::Update(float _dt, std::mt19937_64& _randomEngine)
{
	// 어떤 타이머를 기준으로 하는데 이 타이머가 되면은
	// 내가 들고있는 벡터(ai파이프) 푸시백
	if (m_timer == 0)
	{
		m_timer = TIMER_DURATION;
		m_vecPipe.push_back(AiPipe(m_gamedata, SCREEN_WIDTH, m_Ydistribution(_randomEngine)));
	}
	m_timer--;

	// ai파이프들을 업데이트
	for (AiPipe& p : m_vecPipe)
		p.Update(_dt);
	
	// 지나가서 없애야한다면 erase
	std::vector<AiPipe>::iterator iter = m_vecPipe.begin();
	for (; iter != m_vecPipe.end();)
	{
		if (iter->IsGone())
		{
			iter = m_vecPipe.erase(iter);
		}
		else
			++iter;
	}
}

void AiPipemgr::Render()
{
	for (AiPipe& p : m_vecPipe)
		p.Render();
}


