#pragma once
#include "Bullet.h"
#include "Enemy.h"
enum class CONTORLS
{
	UP, DOWN, LEFT, RIGHT, SHOOT, END
};

class Player
{
private:
	Sprite m_sprite;
	RectangleShape m_hitBox;
	int m_level; int m_exp; int m_expNext;
	int m_hp; int m_hpMax;
	int m_score;
	int m_damage; int m_damageMax;
	Vector2f m_playercenter;



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

	// Gun
	Sprite m_mainGun;
	WEAPON m_eCurWeapon;

	Keyboard::Key m_controls[(int)CONTORLS::END];

	int m_num;
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
private:
	void MoveMent(const float& _dt);
	void Fight(const float& _dt);
	void UiInit();
	void UiUpdate();
	void UiRender();
	void AccessoryUpdate();
};

