#pragma once
#include<SFML/Graphics.hpp>
class Player;

enum EnemyType {
	Default = 0,
	Score = 1,
	Damage = 2,
	Heal = 3,
};

class Ball
{
private:
	sf::CircleShape m_shape;
	EnemyType m_type;
public:
	Ball(const sf::RenderWindow* _window, EnemyType myType);
	virtual ~Ball();
public:
	const sf::CircleShape GetCircle() const { return m_shape; }
	const EnemyType GetType() const { return m_type; }
	bool Update(Player* player, int* score, int* hp);
	void Render(sf::RenderTarget* _target);

};

