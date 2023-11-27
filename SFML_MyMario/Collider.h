#pragma once
class Object;
class Collider
{
public:
	Collider();
	~Collider();
public:
	void FinalUpdate(float _dt);
	void Render();
public:
	void EnterCollision(Collider* _pOther);
	void ExitCollision(Collider* _pOther);
	void StayCollision(Collider* _pOther);
public:
	const UINT& GetID() const { return m_ID; }
	const Object* GetObj() const { return m_pOwner; }
	const Vector2f& GetScale() const { return m_vScale; }
	const Vector2f& GetOffSetPos() const { return m_vOffsetPos; }
	const Vector2f& GetFinalPos() const { return m_vFinalPos; }
private:
	UINT m_check;
	Object* m_pOwner;
	Vector2f m_vOffsetPos; // 오프셋
	Vector2f m_vFinalPos; // 파이널 위치
	Vector2f m_vScale; // 크기
	friend class Object;
	UINT m_ID; // 충돌체 ID값
	static UINT m_sNextID;
};



