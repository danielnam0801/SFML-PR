#pragma once
#include "Gun.h"
class FrontGun : public Gun
{
public:
	// Gun��(��) ���� ��ӵ�
	virtual void Init() override;

	// Gun��(��) ���� ��ӵ�
	virtual void Update() override;
};

