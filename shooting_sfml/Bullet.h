#pragma once
class Bullet
{
public:
	Bullet(Vector2f _pos, float _initvelocity
	,float _maxvelocity, Vector2f _dir, float _acc, WEAPON _eWeapon);
public:
	bool Update(const float& _dt, Sprite _enemy);
	void Render();
private:
	void MoveMent(const float& _dt, Sprite _enemy);
public:
	const WEAPON& GetType() const { return m_eType; }
	const Sprite& GetSprite() const { return m_sprite; }
	const int& GetDamage() const { return m_damage; }
private:
	Vector2f m_enemyradius;
	sf::Clock m_clock;
	float m_theta; // ����
	Sprite m_sprite;
	float  m_maxVelocity; // �ӵ�
	float  m_accerlation; // ���ӵ�
	Vector2f m_dir; // ���� ����
	Vector2f m_curVelocity; // ����ӵ�
	int m_damage;
	WEAPON m_eType;
};

