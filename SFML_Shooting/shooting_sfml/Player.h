#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "TextTag.h"
enum class CONTORLS
{
	UP, DOWN, LEFT, RIGHT, SHOOT, BOMB, END
};

class Player
{
private:
	sf::Clock m_bombclock;
	Sprite m_sprite;
	Sprite m_lwing;
	Sprite m_rwing;
	Sprite m_cPit;
	Sprite m_aura;
	RectangleShape m_hitBox;
	int m_level; int m_exp; int m_expNext;
	int m_hp; int m_hpMax;
	int m_score;
	int m_damage; int m_damageMax;
	Vector2f m_playercenter;
	int m_lwingcntmax; 	int m_lwingcurnum;
	int m_rwingcntmax; 	int m_rwingcurnum;
	int m_cpitcntmax; 	int m_cpitcurnum;
	int m_auracntmax;  	int m_auracurnum;
	// stats
	int m_statPoints;
	int m_str; // 힘 = damage
	int m_dex; // 덱스 = 충돌했을때 miss
	int m_endurance; // 지구력 = hpmax 통이 커져
	int m_defense; // 방어력 = 받는 데미지 감소
	sf::Clock m_clock;

	// timer
	int m_shootTimer; // 총알 딜레이
	int m_shootTimerMax;
	int m_damageTimer; // 데미지 딜레이: 맞고 다시 공격할 수 있는 시간
	int m_damageTimerMax;
	int m_changeTimer;
	int m_changeTimerMax;
	sf::Text m_text;
	sf::RectangleShape m_hpBar;
	sf::RectangleShape m_hpBarback;
	sf::RectangleShape m_expBar;

	vector<Bullet> m_vecbullet;
	// 속도
	float m_maxVelocity; // 최고속도
	float m_acceleration; // 가속도
	Vector2f m_curVelocity; // 현재속도
	Vector2f m_dir;			// 방향
	Vector2f m_normalDir; 
	float m_frictionForce; // 마찰력

	// Gun
	Sprite m_mainGun;
	WEAPON m_eCurWeapon;

	Keyboard::Key m_controls[(int)CONTORLS::END];

	int m_num;
	vector<TextTag> m_vectextTag;
	float m_timer;
	float m_timermax;
public:
	const int& GetTimer() const 
	{ return m_timer; }
public:
	float vectorLength(Vector2f _vec)
	{
		return sqrt(pow(_vec.x, 2) + pow(_vec.y, 2));
	}
	Vector2f Normalize(Vector2f _vec, float _length)
	{
		if (_length == 0)
			return Vector2f(0.f, 0.f);
		else
			return _vec / _length;
	}
public:
	const int& GetScore() const { return m_score; }
	const int& GetNum() const { return m_num; }
	const Sprite& GetSprite() const { return m_sprite; }
	vector<Bullet>& GetBullet() { return m_vecbullet; }
	const bool& IsAlive() const { return m_hp > 0; }
public:
	Player(Keyboard::Key _up, Keyboard::Key _down, Keyboard::Key _left
		  ,Keyboard::Key _right, Keyboard::Key _shoot, Keyboard::Key _bomb, int _num);
	void Update(const float& _dt, vector<Enemy>& _vecenemy);
	void Render();
	void TakeDamage(int _damage);
	bool GainExp(int _exp);
	void TextTagUpdate(const float& _dt);
private:
	void MoveMent(const float& _dt);
	void Fight(const float& _dt);
	void UiInit();
	void UiUpdate();
	void UiRender();
	void AccessoryUpdate();
	void AccessoryChange();
	void TimerUpdate(const float& _dt);
	void CollisionEnemy(const float& _dt, vector<Enemy>& _vecenemy);
	void BulletCollisionEnemy(const float& _dt, vector<Enemy>& _vecenemy);
};

