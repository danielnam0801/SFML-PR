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
	Vector2f m_Force; // ��
	float	 m_fMass; // ����
	Vector2f m_Accel; // ���ӵ�
					// V += at
	Vector2f m_Velocity; //�ӵ�

	float	 m_MaxSpeed; //�ִ� �ӵ�
					//������ = ������� * ��
	float	 m_fricCoef;
};