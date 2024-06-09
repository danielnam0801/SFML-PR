#pragma once
#include<SFML/Graphics.hpp>
enum class BALLTYPE
{
	DEFALUT, DAMAGE, HEAL, END
};
class Ball
{
private:
	sf::CircleShape m_shape;
	BALLTYPE		m_eType;
public:
	Ball(const sf::RenderWindow* _window, BALLTYPE _eType);
	virtual ~Ball();
	const sf::CircleShape& GetShape() const { return m_shape; }
	const BALLTYPE GetType() const { return m_eType; }
public:
	void Update();
	void Render(sf::RenderTarget* _target);
};

