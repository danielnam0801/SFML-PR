#pragma once
class Bullet;
class Player;
class Gun
{
public:
	Gun(Player* player);
	virtual ~Gun();
public:
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render();
	bool Shooting();
public:
	Sprite m_sprite;
	vector<Bullet*> m_bullet;
	float m_cooltime;
	Clock m_clock;
	Player* m_ownerplayer;
};

