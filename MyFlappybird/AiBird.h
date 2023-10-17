#pragma once
#include <SFML/Graphics.hpp>
#include< vector >
#include "AiPipe.h"
#include <random>
class AiBird
{
public:
	AiBird();
	void  Update(float _dt, bool _isMove, std::vector<AiPipe> _pipe);
	void  Render(sf::RenderWindow& _window);
	float GetGapDiff(std::vector<AiPipe> _pipe);
	bool  GetDead() { return m_IsDead; }
	int GetScore() { return m_score; }
	std::vector<std::vector<std::vector<float>>> GetWeight() { return m_weight; }
	void Reset();
	bool operator > (AiBird& b) { return m_fitness > b.m_fitness; }
	bool operator < (AiBird& b) { return m_fitness < b.m_fitness; }
private:
	bool  m_IsDead;
	float m_fSpeed;
	float m_birdx;
	float m_birdy;
	int	  m_score;
	sf::Sprite m_birdsprite;
public:
	void Setting_Weight(std::mt19937_64& _randomengine);
	bool DoArtifcial_Intelligence(std::vector<AiPipe> _pipe);
	void CrossOver(std::mt19937_64& _randomengine
		, std::vector<std::vector<std::vector<float>>> bird1
		, std::vector<std::vector<std::vector<float>>> bird2);
private:
	std::vector<std::vector<std::vector<float>>> m_weight;
	std::uniform_real_distribution<float> m_nodeDistribution;
	std::vector<std::vector<float>> m_neuralnetwork;
	unsigned int m_fitness;
	std::uniform_int_distribution<int> m_mutationDistribution;
};

