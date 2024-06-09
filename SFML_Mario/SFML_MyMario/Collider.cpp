#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "WindowMgr.h"
Collider::Collider()
	: m_vOffsetPos(Vector2f(0.f, 0.f))
{
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(1);
	m_rect.setOrigin(m_rect.getGlobalBounds().width / 2,
		m_rect.getGlobalBounds().height / 2);
	m_rect.setPosition(m_vFinalPos);
}

Collider::~Collider()
{
}

void Collider::FinalUpdate(float _dt)
{
	//Vector2f vPos = m_pOwner->GetPos();
	//m_vFinalPos = vPos + m_vOffsetPos;
	//m_rect.setPosition(m_vFinalPos);
	//m_rect.setSize(m_vScale);
	//vPos += ;
	Vector2f vPos = m_pOwner->GetPos();
	//m_vFinalPos = vPos + m_vOffsetPos;
	m_vFinalPos = vPos;
	m_rect.setPosition(m_vFinalPos);
	m_rect.setSize(m_vScale);
	//m_rect = sf::RectangleShape(m_vScale);

	Vector2f rectpos = m_rect.getPosition();
	//m_rect = sf::Rect(rectpos.x - m_vScale.x / 2
	//		,rectpos.y - m_vScale.y / 2
	//		,m_vScale.x, m_vScale.y);
	
}

void Collider::Render()
{
	if (m_check)
		m_rect.setOutlineColor(Color::Red);
	m_rect.setOutlineColor(Color::Green);
	GET_WINDOW.draw(m_rect);
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
