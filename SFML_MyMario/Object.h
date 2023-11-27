#pragma once
class Collider;
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
private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
	void CreateCollider();
private:
	bool m_IsAlive;
	Collider* m_pCollider;
	string m_strName; // ¿Ã∏ß.
};

