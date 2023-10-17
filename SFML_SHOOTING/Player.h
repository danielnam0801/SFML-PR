#pragma once
#include "Bullet.h"
class Player
{
private:
	Sprite m_Sprite;
	RectangleShape m_hitBox;
	int m_level; int m_exp; int m_expNext;
	int m_hp; int m_hpMax;
	int m_score;
	int m_damage; int m_damageMax;
	vector<Bullet> m_vecbullet;
public:
	Player(bool player1);
	void Update(const float& _dt);
	void Render();
private:
	void MoveMent();
	bool m_isplayer1 = false;
};


