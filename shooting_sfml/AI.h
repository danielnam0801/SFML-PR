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
	State* FindState(ENEMY_STATE _eState);
private:
	map<ENEMY_STATE, State*> m_mapState;
	State* m_pCurState;
	Enemy* m_pOwner;
	friend class Enemy;
};

