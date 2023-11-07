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
	float  m_maxVelocity; // 속도
	float  m_accerlation; // 가속도
	Vector2f m_dir; // 벡터 방향
	Vector2f m_curVelocity; // 현재속도
	int m_damage;
	WEAPON m_weapon;
};

