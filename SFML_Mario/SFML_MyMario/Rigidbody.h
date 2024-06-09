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
	Vector2f m_gravity; // �߰� ���ӵ� �ߵ�������.
	Object* m_pOwner;
	friend class Object;
	// �ʿ��� ��� ����
					// F=MA
	Vector2f m_Force; // ��
	float	 m_fMass; // ����
	Vector2f m_Accel; // ���ӵ�
					// V+=at
	Vector2f m_Velocity; // �ӵ�

	Vector2f m_vMaxVelocity;
	float m_MaxSpeed; // �ִ� �ӵ�
				//f=��N (������ = ������� x ��)
	float m_fricCoef;
};

