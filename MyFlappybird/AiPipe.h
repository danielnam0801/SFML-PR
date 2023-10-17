#pragma once
#include "Core.h"
#include "define.h"

class AiPipe
{
public:
	AiPipe(std::shared_ptr<GameData> _data, int _x, int _y);
	~AiPipe();
	void Update(float _dt);
	void Render();
	bool IsGone() { return m_x <= -2 * BIRD_SIZE; }
	const float& GetX() const { return m_x; }
	const float& GetY() const { return m_y; }
	const int& GetDir() const { return m_dir; }
private:
	std::shared_ptr<GameData> m_gameData;
	float m_x;
	float m_y;
	int m_moveTimer;
	sf::Sprite m_sprite;
	int m_dir;
};

