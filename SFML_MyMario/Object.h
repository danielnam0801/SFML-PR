#pragma once
class Collider;
class Rigidbody;
class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(float _dt) abstract;
	virtual void FinalUpdate(float _dt) final;
	virtual void Render() abstract;
public:
	virtual void EnterCollision(Collider* _pOther);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);
public:
	bool GetIsDead() const { return !m_IsAlive; }
	const string& GetName() const { return m_strName; }
	void SetName(string _name) { m_strName = _name; }
	Collider* GetCollider() { return m_pCollider; }
	Rigidbody* GetRigidbody() { return m_pRigidbody; }
	Sprite& GetSprite() { return m_sprite; }
	const Vector2f& GetPos() const { return m_sprite.getPosition(); }
	const FloatRect& GetScale() const { return m_sprite.getGlobalBounds(); }
	//void SetPos(Vector2f _v) { m_vPos = _v; }
	//void SetScale(Vector2f _v) { m_vScale = _v; }
	void CreateRigidbody();
private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
	void CreateCollider();
private:
	Rigidbody* m_pRigidbody;
	Sprite m_sprite;
	//Vector2f m_vPos;
	//Vector2f m_vScale;
	bool m_IsAlive;
	Collider* m_pCollider;
	string m_strName; // ¿Ã∏ß.
};

