#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
Rigidbody::Rigidbody()
	: m_fMass(1.f)
	, m_Force(Vector2f(0.f,0.f))
	, m_Velocity(Vector2f(0.f,0.f))
	, m_fricCoef(100.f)
	, m_MaxSpeed(10.f)
	, m_vMaxVelocity(Vector2f(200.f, 400.f))
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
	if (fForce >= 0.f)
	{
		m_Accel = m_Force / m_fMass;
	}
	// 힘이 없어도 중력 계속 가속.
	if(m_pOwner->GetGravity())
		m_Accel += m_gravity;
	// 속도
	m_Velocity += m_Accel * _dt;
	// 마찰
	if (m_Velocity.x >= 0.f || m_Velocity.y >= 0.f)
	{
		Vector2f Friction = -m_Velocity;
		Vector2f FrictionDir = Normalize(Friction, Length(Friction));
		Friction = FrictionDir * m_fricCoef * _dt;
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
	//// x 마찰
	//if (m_Velocity.x >= 0.f)
	//{
	//	//float Friction = -m_Velocity.x * m_fricCoef * _dt;
	//	Vector2f Friction = -m_Velocity;
	//	Vector2f FrictionDir = Normalize(Friction, Length(Friction));
	//	
	//	float Frictionx = FrictionDir.x * m_fricCoef * _dt;
	//	if(m_Velocity.x <= Frictionx)
	//	{
	//		m_Velocity = Vector2f(0.f, 0.f);
	//	}
	//	else
	//	{
	//		m_Velocity.x += Frictionx;
	//	}
	//}
	 
	//// 최대 속도 제한
	//float fVelocity = Length(m_Velocity);
	//if (m_MaxSpeed < fVelocity)
	//{
	//	//m_Velocity = Vector2f(m_MaxSpeed, m_MaxSpeed);
	//	m_Velocity = Normalize(m_Velocity, fVelocity);
	//	m_Velocity*= m_MaxSpeed;
	//}
	
	// 속도 제한 검사	
	// 수치로!
	if (abs(m_vMaxVelocity.x < m_Velocity.x)) // 최대속도를 넘어서면?
	{
		sf::Vector2f norvec = Normalize(m_Velocity, Length(m_Velocity));
		m_Velocity.x = norvec.x * m_vMaxVelocity.x;
		//m_Velocity.x = (m_Velocity.x / abs(m_Velocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (abs(m_vMaxVelocity.y < m_Velocity.y)) // 최대속도를 넘어서면?
	{
		sf::Vector2f norvec = Normalize(m_Velocity, Length(m_Velocity));
		m_Velocity.y = norvec.y * m_vMaxVelocity.y;
		//m_Velocity.y = (m_Velocity.y / abs(m_Velocity.y)) * abs(m_vMaxVelocity.y);
	}
	Move(_dt);
	m_Force = Vector2f(0.f, 0.f);
	
	// 가속도와 추가 누적량은 마지막에 초기화
	//m_Accel = Vector2f(0.f, 0.f);
	//m_gravity = Vector2f(0.f, 0.f);
}

void Rigidbody::Move(float _dt)
{
	Vector2f vPos = m_pOwner->GetPos();
	vPos += m_Velocity * _dt;
	//vPos += m_Velocity;
	m_pOwner->GetSprite().setPosition(vPos);
	//	m_pOwner->GetSprite().move(m_Velocity);
}
