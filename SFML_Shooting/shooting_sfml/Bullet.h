#pragma once
class Bullet
{
public:
	Bullet(Vector2f _pos, float _initvelocity
	,float _maxvelocity, Vector2f _dir, float _acc, WEAPON _eWeapon);
public:
	bool Update(const float& _dt);
	void Render();
private:
	void MoveMent(const float& _dt);
public:
	const Sprite& GetSprite() const { return m_sprite; }
	const int& GetDamage() const { return m_damage; }
private:
	Sprite m_sprite;
	float  m_maxVelocity; // �ӵ�
	float  m_accerlation; // ���ӵ�
	Vector2f m_dir; // ���� ����
	Vector2f m_curVelocity; // ����ӵ�
	int m_damage;
	WEAPON m_weapon;
};

