#pragma once
#include "State.h"
class Idle_State : public State
{
public:
	Idle_State();
	~Idle_State();
public:
	virtual void Update(float _dt) override;
	virtual void EnterState() override;
	virtual void ExitState() override;
};

