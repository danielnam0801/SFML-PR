#pragma once
#include "Gun.h"
class FrontGun : public Gun
{
public:
	FrontGun();
public:
	// Gun��(��) ���� ��ӵ�
	virtual void Init() override;
};

