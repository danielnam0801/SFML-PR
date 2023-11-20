#pragma once
#include "State.h"
class AttackAround_State : public State
{
public:
	AttackAround_State();
	~AttackAround_State();
public:
	virtual void Update(float _dt) override;
	virtual void EnterState() override;
	virtual void ExitState() override;
};

