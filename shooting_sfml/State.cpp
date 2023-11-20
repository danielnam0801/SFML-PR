#include "pch.h"
#include "State.h"
#include "AI.h"

State::State(ENEMY_STATE _eState)
	:m_eState(_eState)
{
	m_pEnemy = GetAI()->GetEnemy();
}

State::~State()
{
	if (m_pAI != nullptr)
		delete m_pAI;
	if (m_pEnemy != nullptr)
		delete m_pEnemy;
}
