#include "pch.h"
#include "Goomba.h"
#include "Collider.h"
#include "ResMgr.h"
#include "MyAnimator.h"
#include "WindowMgr.h"
#include "Rigidbody.h"
#include "EventMgr.h"
Goomba::Goomba(sf::Vector2f _pos)
	: m_fSpeed(40.f)

{
	m_tex = ResMgr::GetInst()->GetTexture("Enemies1");
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
		, GetSprite().getGlobalBounds().height / 2);

	GetSprite().setTexture(m_tex);
	GetSprite().setScale(0.5f, 0.5f);
	GetSprite().setTextureRect(sf::Rect(0, 0, 32, 32));
	GetSprite().setPosition(_pos);
	

	// collider
	CreateCollider();
	GetCollider()->SetScale(sf::Vector2f(GetSprite().getGlobalBounds().width,
		GetSprite().getGlobalBounds().height));
	GetCollider()->SetPos(GetSprite().getPosition());

	// animator
	CreateAnimator();
	GetAnimator()->CreateAnim("Walk", &m_tex, Vector2f(0.f, 0.f),
		Vector2f(16.f, 16.f), Vector2f(16.f, 0.f), 2, 0.1f);
	GetAnimator()->CreateAnim("die", &m_tex, Vector2f(32.f, 0.f),
		Vector2f(16.f, 16.f), Vector2f(16.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("fall", &m_tex, Vector2f(0.f, 16.f),
		Vector2f(16.f, 16.f), Vector2f(16.f, -16.f), 1, 0.2f);

	// rigidbody
	//CreateRigidbody();
	eState = GOOMBA_STATE::WALK;
	SetDir(Vector2f(-1.f, 0.f));
	m_vSpeed = Vector2f(40.f,0.f);
	m_kicksound.setBuffer(ResMgr::GetInst()->GetSound("kick"));
}

void Goomba::Update(float _dt)
{
	Vector2f vPos = GetPos();
	if (eState == GOOMBA_STATE::WALK)
	{
		vPos.x += m_vSpeed.x * _dt * GetDir().x;
		vPos.y += m_vSpeed.y * _dt * GetDir().y;
		GetAnimator()->PlayAnim("Walk", true);
	}
	SetPos(vPos);
	GetAnimator()->Update(_dt);
	if (eState == GOOMBA_STATE::DIE)
	{
		static float acctime = 0.f;
		acctime += _dt;
		if (acctime >= 1.f)
		{
			EventMgr::GetInst()->DeleteObject(this);
			acctime = 0.f;

		}
	}
}

void Goomba::Render()
{
	GET_WINDOW.draw(GetSprite());
	Component_Render();
}

void Goomba::EnterCollision(Collider* _pOther)
{
	Object* pObj = _pOther->GetObj();
	Vector2f vObjPos = _pOther->GetFinalPos();
	Vector2f vObjScale = _pOther->GetScale();

	Vector2f vPos = GetCollider()->GetFinalPos();
	Vector2f vScale = GetCollider()->GetScale();
	
	
	// 방향이 위면 이렇게 굼바가 죽음
	if (eState != GOOMBA_STATE::DIE && pObj->GetName() == "Mario" 
		&& pObj->GetDir().y > 0.f)
//		&& (vObjPos.y + vObjScale.y /2) >=(vPos.y - vScale.y /2))
//		&& abs(vObjPos.y - vPos.y) <= (vObjScale.y /2 + vScale.y /2))
	{
		m_fSpeed = 0.f;
 		eState = GOOMBA_STATE::DIE;
		m_kicksound.play();
		GetAnimator()->PlayAnim("die", false);
		pObj->GetRigidbody()->SetVelocity(Vector2f(0.f,-300.f));
	}
	// 방향이 위가 아니면 마리오가 죽음
	if (eState != GOOMBA_STATE::DIE && pObj->GetName() == "Mario"
		&& pObj->GetDir().y <=0.f)
	{
		pObj->SetDead();
	}

}

void Goomba::ExitCollision(Collider* _pOther)
{
	m_vSpeed.y = 500.f;
}

void Goomba::StayCollision(Collider* _pOther)
{
}

void Goomba::MoveUpdate(float _dt)
{
}
