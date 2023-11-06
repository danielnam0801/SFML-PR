#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "TextTag.h"
enum class CONTORLS
{
	UP, DOWN, LEFT, RIGHT, SHOOT, END
};

class Player
{
private:
	Sprite m_sprite;
	Sprite m_lwing;
	Sprite m_rWing;
	Sprite m_cPit;
	Sprite m_aura;
	RectangleShape m_hitBox;
	int m_level; int m_exp; int m_expNext;
	int m_hp; int m_hpMax;
	int m_score;
	int m_damage; int m_damageMax;
	Vector2f m_playercenter;
	
	// stats
	int m_statPoints;
	int m_str; // ��
	int m_dex; // ����
	int m_endurance; // ������
	int m_defense; // ����
	sf::Clock m_clock;

	// timer
	int m_shootTimer; // �Ѿ� ������
	int m_shootTimerMax;
	int m_damageTimer; // ������ ������: �°� �ٽ� ������ �� �ִ� �ð�
	int m_damageTimerMax;
	sf::Text m_text;
	sf::RectangleShape m_hpBar;
	sf::RectangleShape m_hpBarback;
	sf::RectangleShape m_expBar;

	vector<Bullet> m_vecbullet;
	// �ӵ�
	float m_maxVelocity; // �ְ�ӵ�
	float m_acceleration; // ���ӵ�
	Vector2f m_curVelocity; // ����ӵ�
	Vector2f m_dir;			// ����
	float m_frictionForce; // ������

	int m_lwingcntmax;
	int m_lwingcurnum;
	int m_rwingcntmax;
	int m_rwingcurnum;
	int m_cpitcntmax;
	int m_cpitcurnum;
	int m_auracntmax;
	int m_auracurnum;

	int m_changeTimer;
	int m_changeTimerMax;
	// Gun
	Sprite m_mainGun;
	WEAPON m_eCurWeapon;

	Keyboard::Key m_controls[(int)CONTORLS::END];

	int m_num;
	vector<TextTag> m_vectextTag;
public:
	const Sprite& GetSprite() const { return m_sprite; }
	vector<Bullet>& GetBullet() { return m_vecbullet; }
	const bool& IsAlive() const { return m_hp > 0; }
public:
	Player(Keyboard::Key _up, Keyboard::Key _down, Keyboard::Key _left
		  ,Keyboard::Key _right, Keyboard::Key _shoot, int _num);
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

