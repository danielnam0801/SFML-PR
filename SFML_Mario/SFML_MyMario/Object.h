#pragma once
class Collider;
class Rigidbody;
class MyAnimator;
class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(float _dt) abstract;
	virtual void FinalUpdate(float _dt) final;
	virtual void Render() abstract;
	void Component_Render();
public:
	virtual void EnterCollision(Collider* _pOther);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);
public:
	void SetGround(bool _b) { m_IsGround = _b; }
	bool IsGround() { return m_IsGround; }
	bool GetIsDead() const { return !m_IsAlive; }
	const string& GetName() const { return m_strName; }
	void SetName(string _name) { m_strName = _name; }
	Collider* GetCollider() { return m_pCollider; }
	Rigidbody* GetRigidbody() { return m_pRigidbody; }
	Sprite& GetSprite() { return m_sprite; }
	void SetSprite(Sprite _sprite) { m_sprite = _sprite; }
	//void SetTexture(const Texture* _tex) { m_sprite.setTexture(*_tex); }
	const Vector2f& GetPos () const { return m_sprite.getPosition(); }
	const FloatRect& GetScale() const { return m_sprite.getGlobalBounds(); }
	//const Vector2f& GetScale() const { return Vector2f(m_sprite.getGlobalBounds().width
	//													,m_sprite.getGlobalBounds().height); }
	void SetPos(Vector2f _vPos) { m_sprite.setPosition(_vPos); }
	//void SetPos(Vector2f _v) { m_vPos = _v; }
	//void SetScale(Vector2f _v) { m_vScale = _v; }
	void CreateAnimator();
	MyAnimator* GetAnimator() { return m_pAnimator; }
	void CreateRigidbody();
	void CreateCollider();
	bool GetDead() { return m_IsAlive; }
public:
	void SetDead() { m_IsAlive = false; }

	//private:
//	void SetDead() { m_IsAlive = false; }
//	friend class EventMgr;
private:
	bool m_IsGround = false;
	MyAnimator* m_pAnimator;
	Rigidbody* m_pRigidbody;
	Sprite m_sprite;
	//Vector2f m_vPos;
	//Vector2f m_vScale;
	bool m_IsAlive;
	Collider* m_pCollider;
	string m_strName; // ¿Ã∏ß.
public:
	void SetDir(Vector2f _dir) { m_dir = _dir; }
	Vector2f GetDir() { return m_dir; }
	void SetPrevDir(Vector2f _dir) { m_prevdir = _dir; }
	Vector2f GetPrevDir() { return m_prevdir; }
	bool GetGravity() { return m_gravity; }
	void SetGravity(bool _b) { m_gravity = _b; }
private:
	Vector2f m_dir;
	Vector2f m_prevdir;
	bool m_gravity = false;
};

