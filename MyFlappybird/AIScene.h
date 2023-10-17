#pragma once
#include "Scene.h"
#include "AiBird.h"
#include "Core.h"
#include "AiPipeManager.h"

class AIScene : public Scene
{
public:
	AIScene(std::shared_ptr<GameData> _data);
	~AIScene();
	void Init();
	void Update(float _dt) override;
	void Render() override;
private:
	std::shared_ptr<GameData> m_gameData;
	sf::Sprite m_background;
	sf::Text m_aiText;
	std::vector<AiBird> m_vecBird;
	int m_Score;
	int m_generation;
	int m_gameSpeed;
	AiPipeManager m_pipeManager;
};


