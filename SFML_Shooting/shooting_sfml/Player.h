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
	
	// stats
	int m_statPoints;
	int m_str; // ��
	int m_dex; // ����
	int m_endurance; // ������
	int m_defense; // ����
	sf::Clock m_clock;
	
	//Accessories
	int m_lwingcntmax;
	int m_lwingcurnum;
	int m_rwingcntmax;
	int m_rwingcurnum;
	int m_cpitcntmax;
	int m_cpitcurnum;
	int m_auracntmax;
	int m_auracurnum;

	// timer
	int m_shootTimer; // �Ѿ� ������
	int m_shootTimerMax;
	int m_damageTimer; // ������ ������: �°� �ٽ� ������ �� �ִ� �ð�
	int m_damageTimerMax;
	int m_freezeTimer; //����
	int m_freezeTimerMax;
	int m_changeTimer; //�ǻ� ����
	int m_changeTimerMax;
	sf::Text m_text;
	sf::Text m_infoText;
	sf::RectangleShape m_hpBar;
	sf::RectangleShape m_hpBarback;
	sf::RectangleShape m_expBar;
	sf::Clock m_bombClock;

	vector<Bullet> m_vecbullet;
	// �ӵ�
	float m_maxVelocity; // �ְ�ӵ�
	float m_acceleration; // ���ӵ�
	Vector2f m_curVelocity; // ����ӵ�
	Vector2f m_dir;			// ����
	Vector2f m_normalDir;
	float m_frictionForce; // ������

	// Gun
	Sprite m_mainGun;
	WEAPON m_eCurWeapon;

	Keyboard::Key m_controls[(int)CONTORLS::END];

	int m_num;
	vector<TextTag> m_vectextTag;
	float m_timer;
	float m_timermax;
public:
	const int& GetNum() const { return m_num; }
	const int& GetTimer() const { return m_timer; }
	const int& GetScore() const { return m_score; }
	const bool& IsAlive() const { return m_hp > 0; }
	const Sprite& GetSprite() const { return m_sprite; }
	vector<Bullet>& GetBullet() { return m_vecbullet; }
public:
	Player(Keyboard::Key _up, Keyboard::Key _down, Keyboard::Key _left
		  ,Keyboard::Key _right, Keyboard::Key _shoot, Keyboard::Key _bomb, int _num);
	void Update(const float& _dt, vector<Enemy>& _vecenemy);
	void Render();
	void TakeDamage(int _damage);
	bool GainExp(int _exp);
	void TextTagUpdate(const float& _dt);
	void ItemAbillity(ITEM_TYPE _eType);
public:
		float vectorLength(Vector2f _vec)
		{
			return sqrt(pow(_vec.x, 2) + pow(_vec.y, 2));
		}
		Vector2f Normalize(Vector2f _vec, float _length)
		{
			if (_length == 0)
				return Vector2f(0.f, 0.f);
			return _vec / _length;
		}
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
	void BulletCollisionEnemy(const float& _dt, vector <Enemy>& _vecenemy);
};

