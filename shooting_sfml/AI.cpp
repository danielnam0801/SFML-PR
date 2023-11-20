#include "pch.h"
#include "AI.h"
#include "State.h"

AI::AI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

AI::~AI()
{
	map<ENEMY_STATE, State*>::iterator iter;
	for (iter = m_mapState.begin(); iter != m_mapState.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapState.clear();
}

void AI::Update(float _dt)
{
	if (m_pCurState != nullptr)
		m_pCurState->Update(_dt);
}

void AI::AddState(State* _pState)
{
	State* pState = FindState(_pState->GetType());
	m_pCurState = _pState;
	m_mapState.insert({ _pState->GetType(), _pState });
}

State* AI::FindState(ENEMY_STATE _eState)
{
	map<ENEMY_STATE, State*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;
	return iter->second;
}
