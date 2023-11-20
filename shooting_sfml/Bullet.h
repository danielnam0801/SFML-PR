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
	float m_theta; // 각도
	Sprite m_sprite;
	float  m_maxVelocity; // 속도
	float  m_accerlation; // 가속도
	Vector2f m_dir; // 벡터 방향
	Vector2f m_curVelocity; // 현재속도
	int m_damage;
	WEAPON m_eType;
};

