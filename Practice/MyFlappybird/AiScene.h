#pragma once
#include "Scene.h"
#include "Core.h"
#include "AiBird.h"
#include "AiPipemgr.h"
class AiScene : public Scene
{
public:
	AiScene(std::shared_ptr<GameData> _data);
	~AiScene();
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	std::shared_ptr<GameData> m_gamedata;
	sf::Sprite m_background;
	sf::Text m_aitext;
	std::vector<AiBird> m_vecBird;
	int m_Score;
	int m_generation;
	int m_gamespeed;
	AiPipemgr m_pipemgr;
};

