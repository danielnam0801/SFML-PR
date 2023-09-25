#pragma once
#include "Core.h"
#include<random>
class AiPipe;
class AiPipeManager
{
public:
	AiPipeManager(std::shared_ptr<GameData> _data);
	void Update(float _dt, std::mt19937_64& _randomEngine);
	void Render();
	void Reset();
	std::vector<AiPipe> GetPipe() { return m_vecPipe; }
private:
	std::shared_ptr<GameData> m_gameData;
	std::vector<AiPipe> m_vecPipe;
	std::uniform_int_distribution<int> m_Ydistribution;
	int m_timer;
};

