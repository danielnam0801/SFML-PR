#pragma once
#include "Gun.h"
class FrontGun : public Gun
{
public:
	// Gun을(를) 통해 상속됨
	virtual void Init() override;

	// Gun을(를) 통해 상속됨
	virtual void Update() override;
};

