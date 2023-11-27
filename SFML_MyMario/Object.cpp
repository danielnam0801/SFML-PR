#include "pch.h"
#include "Object.h"
#include "Collider.h"
Object::Object()
	: m_IsAlive(true)
{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void Object::FinalUpdate(float _dt)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->FinalUpdate(_dt);
	}
}


void Object::EnterCollision(Collider* _pOther)
{
}

void Object::ExitCollision(Collider* _pOther)
{
}

void Object::StayCollision(Collider* _pOther)
{
}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}
