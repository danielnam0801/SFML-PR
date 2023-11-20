#pragma once
class State;
class Enemy;
class AI
{
public:
	AI();
	~AI();
public:
	void Update(float _dt);
	void AddState(State* _pState);
	void SetState(ENEMY_STATE _eState)
	{
		m_pCurState = FindState(_eState);
	}
	State* FindState(ENEMY_STATE _eState);
	void ChangeState(ENEMY_STATE _eState);
public:
	Enemy* GetEnemy() const
	{
		return m_pOwner;
	}
private:
	map<ENEMY_STATE, State*> m_mapState;
	State* m_pCurState;
	Enemy* m_pOwner;
	friend class Enemy;
};

