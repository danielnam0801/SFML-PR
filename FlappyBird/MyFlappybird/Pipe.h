#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include "Core.h"
class Pipe
{
public:
	Pipe(std::shared_ptr<GameData> _data);
	void Update(float _dt);
	void Render();
	void SpawnUpdate();
	void SetRandomOffset() { m_pipeOffset = rand() % (m_landHeight + 1); }
	const std::vector<sf::Sprite>& GetSprite() const { return m_vecPipeSprite; }
	std::vector<sf::Sprite>& GetScoreSprite() { return m_vecScorePipeSprite; }

private:
	void SpawnPipeUp();
	void SpawnPipeDown();
	void SpawnScorePipe();
private:
	std::shared_ptr<GameData> m_gamedata;
	std::vector<sf::Sprite> m_vecPipeSprite;
	std::vector<sf::Sprite> m_vecScorePipeSprite;
	int m_landHeight;
	int m_pipeOffset;
};

