#pragma once
#include <assert.h>
class Enemy
{
public:
	Enemy(Vector2f _pos, Vector2f _dir, Vector2f _scale, ENEMY _eType,
		int _hpMax, int _damagemin, int _damagemax, int _follownum);
public:
	void TakeDamage(int _damage);
	bool Update(const float& _dt, Vector2f _playerPos);
	void Render();
private:
	void MoveMent(const float& _dt, Vector2f _playerPos);
	void UiUpdate();
public:
					// 데미지를 1 ~ 10
	const int& GetDamage() const { return rand() % (m_damagemax - m_damagemin)+ m_damagemin; }
	const Sprite& GetSprite() const { return m_sprite; }
	const int& GetHp() const { return m_hp; }
	const int& GetHpMax() const { return m_hpMax; }
	const bool& GetIsDead() const { return m_hp <= 0; }
	const int& GetFollowNum() const { return m_followNum; }
public:
	float vectorLength(Vector2f _vec)
	{
		return sqrt(pow(_vec.x, 2) + pow(_vec.y, 2));
	}
	Vector2f Normalize(Vector2f _vec, float _length)
	{
		assert(_length != 0.f);
		return _vec / _length;
	}
	int m_followNum;
	Vector2f m_dir;
	Vector2f m_normalizedir;
private:
	Sprite m_sprite;
	ENEMY m_eType;
	int  m_hp; int m_hpMax;
	int m_damagemin; int m_damagemax;
	Vector2f m_dir;
	sf::RectangleShape m_hpBar;
	sf::RectangleShape m_hpBarback;
};

