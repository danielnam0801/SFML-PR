#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include "Core.h"
class Pipe
{
public:
	Pipe(std::shared_ptr<GameData> _dat);
	void Update(float _dt);
	void Render();
private:
	void SpawnPipeUp();
	void SpawnPipeDown();
	void SpawnPipeMiddle();
	void SpawnUpdate();
	void DeletePipeCheck();
	void SetRandomOffset() { m_pipeOffset = rand() % (m_landHeight + 1); }
private:
	std::shared_ptr<GameData> m_gameData;
	std::vector<sf::Sprite> m_vecpipesprite;
	std::vector<sf::Sprite> m_vecscorepipesprite;
	sf::Clock m_clock;
	int randValue;
public:
	int m_landHeight;
	int m_pipeOffset;
	const std::vector<sf::Sprite>& GetSprite() const { return m_vecpipesprite; }
	std::vector<sf::Sprite>& GetScorePipeSprite() { return m_vecscorepipesprite; }
};

