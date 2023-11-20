#pragma once
class AI; class Enemy;
class State
{
public:
	State(ENEMY_STATE _eState);
	virtual ~State();
public:
	virtual void Update(float _dt) abstract;
	virtual void EnterState() abstract;
	virtual void ExitState() abstract;
public:
	const ENEMY_STATE& GetType() const
	{
		return m_eState;
	}
	AI* GetAI() const
	{
		return m_pAI;
	}
protected:
	ENEMY_STATE m_eState;
	AI* m_pAI;
	Enemy* m_pEnemy;
	friend class AI;
};

