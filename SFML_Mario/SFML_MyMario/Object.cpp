#include "pch.h"
#include "Object.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "MyAnimator.h"
Object::Object()
	: m_IsAlive(true)
{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void Object::CreateAnimator()
{
	m_pAnimator = new MyAnimator;
	m_pAnimator->m_pOwner = this;
}

void Object::CreateRigidbody()
{
	m_pRigidbody = new Rigidbody;
	m_pRigidbody->m_pOwner = this;
}
void Object::FinalUpdate(float _dt)
{
	if (nullptr != m_pRigidbody)
	{
		m_pRigidbody->FinalUpdate(_dt);
	}

	if (nullptr != m_pCollider)
	{
		m_pCollider->FinalUpdate(_dt);
	}
}

void Object::Component_Render()
{
	if (nullptr != m_pAnimator)
		m_pAnimator->Render();
	if (nullptr != m_pCollider)
		m_pCollider->Render();
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

