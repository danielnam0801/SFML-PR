#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Rigidbody.h"
#include"WindowMgr.h"
Ground::Ground(sf::Sprite& _sprite)
{
	SetSprite(_sprite);
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
						, GetSprite().getGlobalBounds().height / 2);
	CreateCollider();
	GetCollider()->SetScale(sf::Vector2f(_sprite.getGlobalBounds().width,
							_sprite.getGlobalBounds().height));
}

void Ground::Update(float _dt)
{
}

void Ground::Render()
{
	//GET_WINDOW.draw(GetSprite());
	Component_Render();
}

void Ground::EnterCollision(Collider* _pOther)
{
	Object* pObj = _pOther->GetObj();
	if (pObj->GetName() == "Mario") // pObj->GetName() == "Goomba")
	{
		pObj->SetGround(true);
		if (pObj->IsGround())
		{
			// 경직
			//pObj->GetRigidbody()->SetVelocity(Vector2f(0.f, 0.f));

			// 원래
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
		//vObjPos.y -= (fValue -1.f); // 1픽셀 더 밀어서 달달달 안거리게
		vObjPos.y -= (fValue); // 1픽셀 더 밀어서 달달달 안거리게
		pObj->SetPos(vObjPos);
	}

	//if (pObj->GetName() == "Goomba")
//{
//	pObj->SetGround(true);
//	if (pObj->IsGround())
//	{
//		Vector2f velocity = pObj->GetRigidbody()->GetVelocity();
//		pObj->GetRigidbody()->SetVelocity(Vector2f(velocity.x, 0.f));
//	}
//	Vector2f vObjPos = _pOther->GetFinalPos();
//	Vector2f vObjScale = _pOther->GetScale();

//	Vector2f vPos = GetCollider()->GetFinalPos();
//	Vector2f vScale = GetCollider()->GetScale();
//	float fLen = abs(vObjPos.y - vPos.y);
//	float fValue = (vObjScale.y / 2.8f + vScale.y / 2.8f) - fLen;
//	vObjPos = pObj->GetPos();
//	//vObjPos.y -= (fValue -1.f); // 1픽셀 더 밀어서 달달달 안거리게
//	vObjPos.y -= (fValue); // 1픽셀 더 밀어서 달달달 안거리게
//	pObj->SetPos(vObjPos);
//}
	//Object* pObj = _pOther->GetObj();
	//if (pObj->GetName() == "Mario")
	//{
	//	pObj->SetGround(true);
	//	Vector2f vObjPos = _pOther->GetFinalPos();
	//	Vector2f vObjScale = _pOther->GetScale();

	//	Vector2f vPos = GetCollider()->GetFinalPos();
	//	Vector2f vScale = GetCollider()->GetScale();
	//	float fLen = abs(vObjPos.y - vPos.y);
	//	float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;
	//	vObjPos = pObj->GetPos();
	//	//vObjPos.y -= (fValue -1.f); // 1픽셀 더 밀어서 달달달 안거리게
	//	vObjPos.y -= (fValue); // 1픽셀 더 밀어서 달달달 안거리게
	//	pObj->SetPos(vObjPos);
	//}
}

void Ground::ExitCollision(Collider* _pOther)
{
	Object* pObj = _pOther->GetObj();
	if (pObj->GetName() == "Mario")
	{
		pObj->SetGround(false);
	}
	if (pObj->GetName() == "Goomba")
	{
		pObj->SetGround(false);
	}
}

void Ground::StayCollision(Collider* _pOther)
{
	/*Object* pObj = _pOther->GetObj();
	if (pObj->GetName() == "Mario")
	{
		pObj->SetGround(true);
		Vector2f vObjPos = _pOther->GetFinalPos();
		Vector2f vObjScale = _pOther->GetScale();

		Vector2f vPos = GetCollider()->GetFinalPos();
		Vector2f vScale = GetCollider()->GetScale();
		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;
		vObjPos = pObj->GetPos();
		vObjPos.y -= fValue;
		pObj->SetPos(vObjPos);
	}*/
	//Object* pObj = _pOther->GetObj();
	//if (pObj->GetName() == "Mario")
	//{
	//	pObj->SetGround(true);
	//	Vector2f vObjPos = _pOther->GetFinalPos();
	//	Vector2f vObjScale = _pOther->GetScale();

	//	Vector2f vPos = GetCollider()->GetFinalPos();
	//	Vector2f vScale = GetCollider()->GetScale();
	//	float fLen = abs(vObjPos.y - vPos.y);
	//	float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;
	//	vObjPos = pObj->GetPos();
	//	//vObjPos.y -= (fValue -1.f); // 1픽셀 더 밀어서 달달달 안거리게
	//	vObjPos.y -= (fValue / 4.f); // 1픽셀 더 밀어서 달달달 안거리게
	//	pObj->SetPos(vObjPos);
	//}
}
