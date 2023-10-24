#pragma once
class Bullet
{
public:
	Bullet(Vector2f _pos, float _initvelocity, float _maxv,
		 Vector2f dir, float _acc, WEAPON _weapon);
public:
	bool Update(const float& _dt);
	void Render();
private:
	const Sprite& GetSprite() const { return m_Sprite; }
	void MoveMent();
private:
	Sprite m_Sprite;
	float m_maxVelocity;
	float m_acceleration;
	Vector2f m_curVelocity;
	Vector2f m_dir;
	sf::Clock m_clock;
};

