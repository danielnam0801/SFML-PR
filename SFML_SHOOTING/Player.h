#pragma once
#include "Bullet.h"
class Player
{
private:
	Sprite m_Sprite;
	RectangleShape m_hitBox;
	Text m_hpText;
	int m_level; int m_exp; int m_expNext;
	int m_hp; int m_hpMax;
	int m_score;
	int m_damage; int m_damageMax;

	//timer
	int m_shootTimer;
	int m_shootTimerMax;
	int m_damageTimer;
	int m_damageTimerMax;

	vector<Bullet> m_vecbullet;
	float m_maxVelocity;
	float m_acceleration;
	float m_frictionForce;
	Vector2f m_curVelocity;
	Vector2f m_dir;
public:
	Player(bool player1, Vector2f _pos, float _initVelocity, 
		float _maxvelocity, Vector2f _dir, float _acc, float _dcc);
	void Update(const float& _dt);
	void Render();
	const Sprite& GetSprite() const{ return m_Sprite; }
private:
	void MoveMent();
	void Fight(const float& _dt);
	void SetHpText();
	bool m_isplayer1 = false;
};


