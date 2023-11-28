#include "pch.h"
#include "Collider.h"
#include "Object.h"
Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::FinalUpdate(float _dt)
{
	Vector2f vPos = m_pOwner->GetPos();
	
}

void Collider::Render()
{
}

void Collider::EnterCollision(Collider* _pOther)
{
	++m_check;
	m_pOwner->EnterCollision(_pOther);
}

void Collider::ExitCollision(Collider* _pOther)
{
	--m_check;
	m_pOwner->ExitCollision(_pOther);
}

void Collider::StayCollision(Collider* _pOther)
{
	m_pOwner->StayCollision(_pOther);
}
