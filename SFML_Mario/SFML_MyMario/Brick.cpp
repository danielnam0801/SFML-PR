#include "pch.h"
#include "Brick.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "WindowMgr.h"
#include "ResMgr.h"
Brick::Brick(sf::Sprite& _sprite)
	: m_velocity(0.f,0.f)
{
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
		, GetSprite().getGlobalBounds().height / 2);
	SetSprite(_sprite);

	CreateCollider();
	GetCollider()->SetScale(sf::Vector2f(_sprite.getGlobalBounds().width,
		_sprite.getGlobalBounds().height));

	CreateRigidbody();
	m_bumpsound.setBuffer(ResMgr::GetInst()->GetSound("bump"));
	m_breaksound.setBuffer(ResMgr::GetInst()->GetSound("breakblock"));
}

void Brick::Update(float _dt)
{
	if (m_IsBroken)
	{
		static float ypos = GetSprite().getPosition().y;
		GetSprite().move(m_velocity);
		//float value = m_velocity.y + 3.f * _dt;			
		if (GetSprite().getPosition().y > ypos)
		{
			m_velocity.y =0.f;
			m_IsBroken = false;
		}
		else
			m_velocity.y += 10.f * _dt;

		//if (ypos >= value)
		//	GetSprite().setPosition(Vector2f(GetSprite().getPosition().x, ypos));
	}
}

void Brick::Render()
{
	GET_WINDOW.draw(GetSprite());
	Component_Render();
}

void Brick::EnterCollision(Collider* _pOther)
{
	Object* pObj = _pOther->GetObj();
	if (pObj->GetName() == "Mario")
	{
		if (pObj->GetDir().y < 0.f)
		{
			m_bumpsound.play();
			m_IsBroken = true;
			m_velocity.y = -3.f;
			//GetRigidbody()->SetVelocity(Vector2f(pObj->GetRigidbody()->GetVelocity().x, 0.f));
			//// ������
			//Vector2f vObjPos = _pOther->GetFinalPos();
			//Vector2f vObjScale = _pOther->GetScale();

			//// �긯
			//Vector2f vPos = GetCollider()->GetFinalPos();
			//Vector2f vScale = GetCollider()->GetScale();
			//
			//vObjPos.y = vPos.y + vScale.y / 2;
			//pObj->SetPos(vObjPos);

			pObj->GetRigidbody()->SetVelocity(Vector2f(0.f, 0.f));
		}
		else if(pObj->GetDir().y > 0.f)
		{
			pObj->SetGround(true);
			if (pObj->IsGround())
			{
				// ����
				//pObj->GetRigidbody()->SetVelocity(Vector2f(0.f, 0.f));

				// ����
				Vector2f velocity = pObj->GetRigidbody()->GetVelocity();
				pObj->GetRigidbody()->SetVelocity(Vector2f(velocity.x, 0.f));
			}
			Vector2f vObjPos = _pOther->GetFinalPos();
			Vector2f vObjScale = _pOther->GetScale();

			Vector2f vPos = GetCollider()->GetFinalPos();
			Vector2f vScale = GetCollider()->GetScale();
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 3.f + vScale.y / 3.f) - fLen;
			vObjPos = pObj->GetPos();
			//vObjPos.y -= (fValue -1.f); // 1�ȼ� �� �о �޴޴� �ȰŸ���
			vObjPos.y -= (fValue); // 1�ȼ� �� �о �޴޴� �ȰŸ���
			pObj->SetPos(vObjPos);

		}
	}
}

void Brick::ExitCollision(Collider* _pOther)
{

}

void Brick::StayCollision(Collider* _pOther)
{
}
