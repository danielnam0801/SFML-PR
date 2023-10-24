#pragma once
#include "Bullet.h"

class FrontGun;

enum class InputType
{
	UP, DOWN, LEFT, RIGHT, Attack, END	
};

class Player
{
private:
	Vector2f m_playercenter;
	Sprite m_maingun;
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

	WEAPON m_curWeapon;
	vector<Bullet> m_vecbullet;
	float m_maxVelocity;
	float m_acceleration;
	float m_frictionForce;
	Vector2f m_curVelocity;
	Vector2f m_dir;
	std::vector<sf::Keyboard::Key> inputs;
public:
	Player(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, Keyboard::Key space,
		 float _initVelocity, 
		float _maxvelocity, Vector2f _dir, float _acc, float _dcc);
	void Update(const float& _dt);
	void Render();
	const Sprite& GetSprite() const{ return m_Sprite; }
private:
	void MoveMent();
	void Fight(const float& _dt);
	void UiInit();
	void UiUpdate();
	void UiRender();
	void Accessorypdate();
};


