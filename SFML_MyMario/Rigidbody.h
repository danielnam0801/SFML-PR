#pragma once
class Object;
class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();
public:
	void FinalUpdate(float _dt);
	void Move(float _dt);
	void AddForce(Vector2f _force)
	{
		m_Force += _force;
	}
	void SetVelocity(Vector2f _v)
	{
		m_Velocity = _v;
	}
	void AddVelocity(Vector2f _v)
	{
		m_Velocity += _v;
	}
	void SetMaxSpeed(float _f)
	{
		m_MaxSpeed = _f;
	}
private:
	Object* m_pOwner;
	friend class Object;
	Vector2f m_Force; // 힘
	float	 m_fMass; // 질량
	Vector2f m_Accel; // 가속도
					// V += at
	Vector2f m_Velocity; //속도

	float	 m_MaxSpeed; //최대 속도
					//마찰력 = 마찰계수 * 힘
	float	 m_fricCoef;
};