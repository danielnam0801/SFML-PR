#pragma once
class Object;
class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();
public:
	Vector2f GetVelocity() { return m_Velocity; }
	//float GetSpeed() { return Length(m_Velocity); }
	float GetSpeed() { return Length(m_Velocity); }
	void FinalUpdate(float _dt);
	void AddForce(Vector2f _force)
	{
		m_Force+= _force;
	}
	void SetVelocity(Vector2f _v)
	{
		m_Velocity = _v;
	}
	void AddVelocity(Vector2f _v)
	{
		m_Velocity += _v;
	}
	Vector2f GetMaxVelocity() { return m_vMaxVelocity; }
	void SetMaxSpeed(float _f)
	{
		m_MaxSpeed = _f;
	}
	void SetGravity(Vector2f _accel)
	{
		//m_Accel += _accel;
		m_gravity = _accel;
	}
private:
	void Move(float _dt);
private:
	Vector2f m_gravity; // 추가 가속도 추뎀같은거.
	Object* m_pOwner;
	friend class Object;
	// 필요한 멤버 변수
					// F=MA
	Vector2f m_Force; // 힘
	float	 m_fMass; // 질량
	Vector2f m_Accel; // 가속도
					// V+=at
	Vector2f m_Velocity; // 속도

	Vector2f m_vMaxVelocity;
	float m_MaxSpeed; // 최대 속도
				//f=μN (마찰력 = 마찰계수 x 힘)
	float m_fricCoef;
};

