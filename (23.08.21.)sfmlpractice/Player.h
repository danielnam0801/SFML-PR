#pragma once
#include<SFML/Graphics.hpp>
class Player
{
private:
	sf::RectangleShape m_shape;
	sf::Texture		   m_tex;
	
	float			   m_fmovespeed;
	int				   m_iHP;
	int				   m_iHpMax;
public:
	Player(float _x = 0.f, float _y =0.f);
	virtual ~Player();
public:
	void Update(sf::RenderWindow* _window);
	void Render(sf::RenderTarget* _target);
public:
	const sf::RectangleShape& GetShape() const { return m_shape; }
	const int& GetHp() const { return m_iHP; }
	const int& GetHpMax() const { return m_iHpMax; }
	void TakeDamage(const int& _damage);
	void GainHeal(const int& _heal);
	// todo: hp.. key update..
private:
	void UpdateInput();
	void UpdateWindowCollision(const sf::RenderWindow* _window);
};

