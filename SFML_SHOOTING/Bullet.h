#pragma once
class Bullet
{
public:
	Bullet(Vector2f _pos, float _maxv = -15.f);
public:
	void Update(const float& _dt);
	void Render();
private:
	void MoveMent();
private:
	Sprite m_Sprite;
	float m_maxVelocity;
	float m_curVelocity;
	sf::Clock m_clock;
};

