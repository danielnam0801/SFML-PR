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
	Object* GetObj() const { return m_pOwner; }
	const Vector2f& GetScale() const { return m_vScale; }
	/*const Vector2f& GetScale() const { return Vector2f(m_rect.getGlobalBounds().width,
													m_rect.getGlobalBounds().height); }
	*/
	RectangleShape& GetRect() { return m_rect; }
	const Vector2f& GetOffSetPos() const { return m_vOffsetPos; }
	void SetOffsetPos(Vector2f _v) { m_vOffsetPos = _v; }
	const Vector2f& GetFinalPos() const { return m_vFinalPos; }
	//const Vector2f& GetFinalPos() const { return m_rect.getPosition(); }
	void SetPos(Vector2f _Pos)
	{
		//m_rect.setPosition(_Pos);
		m_vFinalPos = _Pos;
	}
	void SetScale(Vector2f _Scale)
	{
		//m_rect.setScale(_Scale);
		m_vScale = _Scale;
	}
private:
	sf::RectangleShape m_rect;
	UINT m_check;
	Object* m_pOwner;
	Vector2f m_vOffsetPos; // 오프셋
	Vector2f m_vFinalPos; // 파이널 위치
	Vector2f m_vScale; // 크기
	friend class Object;
	UINT m_ID; // 충돌체 ID값
	static UINT m_sNextID;
};



