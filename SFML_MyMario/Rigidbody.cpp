#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
Rigidbody::Rigidbody()
	: m_fMass(1.f)
	, m_Force(Vector2f(0.f,0.f))
	, m_Velocity(Vector2f(0.f,0.f))
	, m_fricCoef(0.1f)
	, m_MaxSpeed(10.f)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::FinalUpdate(float _dt)
{

	// F = ma
	// a = F / m 
	// v+=at
	// S = V*T
	float fForce = Length(m_Force);
	//if (fForce != 0.f)
	{
		m_Accel = m_Force / m_fMass;
		m_Velocity += m_Accel * _dt;
	}

	// 마찰
	if (m_Velocity.x != 0.f || m_Velocity.y != 0.f)
	{
		Vector2f Friction = -m_Velocity;
		Vector2f FrictionDir = Normalize(Friction, Length(Friction));
		Friction = FrictionDir * m_fricCoef;
		//Vector2f FrictionDir = -Normalize(m_Velocity, Length(m_Velocity) * m_fricCoef);

		if (Length(m_Velocity) <= Length(Friction))
		{
			m_Velocity = Vector2f(0.f, 0.f);
		}
		else
		{
			m_Velocity += Friction;
		}

	}

	// 최대 속도 제한
	float fVelocity = Length(m_Velocity);
	if (m_MaxSpeed < fVelocity)
	{
		//m_Velocity = Vector2f(m_MaxSpeed, m_MaxSpeed);
		m_Velocity = Normalize(m_Velocity, fVelocity);
		m_Velocity*= m_MaxSpeed;
	}
	Move(_dt);
	m_Force = Vector2f(0.f, 0.f);
}

void Rigidbody::Move(float _dt)
{
	Vector2f vPos = m_pOwner->GetPos();
	vPos += m_Velocity * _dt;
	//vPos += m_Velocity;
	m_pOwner->GetSprite().setPosition(vPos);
	//	m_pOwner->GetSprite().move(m_Velocity);
}
