#pragma once
#include"Core.h"
#include<SFML/Graphics.hpp>
#include<vector>
enum class BIRDSTATE
{
	IDLE, FLY, FALL
};
class Bird
{
public:
	Bird(std::shared_ptr<GameData> _data);
	void Update(float _dt);
	void Animate(float _dt);
	void Render();
	void Tap();
	const sf::Sprite GetSprite() const { return m_birdsprite; }
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Sprite				  m_birdsprite;
	std::vector<sf::Texture>  m_vecanim;
	size_t					  m_animiter;
	float					  m_anitime;
	BIRDSTATE				  m_ebirdState;
	sf::Clock				  m_movementclock;
	float					  m_rotate;
};
