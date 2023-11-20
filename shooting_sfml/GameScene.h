#pragma once
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "TextTag.h"
class GameScene : public Scene
{
public:
	void Init() override;
	void Update(float _dt) override;
	void Render() override;
private:
	void UiUpdate(float _dt);
	void EnemyUpdate(float _dt);
	void PlayerUpdate(float _dt);
	void EnemySpawnUpdate();
private:
	int m_StageWave;
	bool m_IsStageClear;
	GAME_STAGE m_eStage;
	std::vector<TextTag> m_vecTextTag;
	//std::shared_ptr<Player> m_pPlayer;
	std::vector<std::shared_ptr<Player>> m_vecPlayer;
	std::vector<Enemy> m_vecEnemy;
	Sprite m_background;
//	sf::Text m_text;
	sf::Clock m_clock;
	sf::Text m_gameOverText;
	sf::Text m_scoreText;
	sf::Text m_timertext;
};
