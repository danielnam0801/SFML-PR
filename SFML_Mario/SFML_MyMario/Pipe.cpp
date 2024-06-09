#include "pch.h"
#include "Pipe.h"
#include "Collider.h"
#include "Rigidbody.h"
Pipe::Pipe(sf::Sprite& _sprite)
{
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
		, GetSprite().getGlobalBounds().height / 2);
	SetSprite(_sprite);
	CreateCollider();
	GetCollider()->SetScale(sf::Vector2f(_sprite.getGlobalBounds().width,
		_sprite.getGlobalBounds().height));
}

void Pipe::Update(float _dt)
{
}

void Pipe::Render()
{
	Component_Render();
}

void Pipe::EnterCollision(Collider* _pOther)
{
	Object* pObj = _pOther->GetObj();
	if (pObj->GetName() == "Goomba")
	{
		Vector2f dir = pObj->GetDir();
		dir.x *= -1;
		pObj->SetDir(dir);
	}
	if (pObj->GetName() == "Mario") // pObj->GetName() == "Goomba")
	{
		pObj->SetGround(true);
		if (pObj->IsGround())
		{
			Vector2f velocity = pObj->GetRigidbody()->GetVelocity();
			pObj->GetRigidbody()->SetVelocity(Vector2f(velocity.x, 0.f));
		}
		Vector2f vObjPos = _pOther->GetFinalPos();
		Vector2f vObjScale = _pOther->GetScale();

		Vector2f vPos = GetCollider()->GetFinalPos();
		Vector2f vScale = GetCollider()->GetScale();
		if (vPos.y >= vObjPos.y)
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 3.f + vScale.y / 3.f) - fLen;
			vObjPos = pObj->GetPos();
			//vObjPos.y -= (fValue -1.f); // 1픽셀 더 밀어서 달달달 안거리게
			vObjPos.y -= (fValue); // 1픽셀 더 밀어서 달달달 안거리게
			pObj->SetPos(vObjPos);
		}
	}
}

void Pipe::ExitCollision(Collider* _pOther)
{
}

void Pipe::StayCollision(Collider* _pOther)
{
}
