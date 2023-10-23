#pragma once
class Bullet
{
public:
	Bullet(Vector2f _pos, float _initvelocity, float _maxv,
		Vector2f curVelocity, Vector2f dir);
public:
	void Update(const float& _dt);
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

