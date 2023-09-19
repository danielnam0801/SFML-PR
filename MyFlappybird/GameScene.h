#pragma once
#include "Scene.h"
#include "Core.h"
#include "Collision.h"
enum class GAMESTATE
{
	IDLE, PLAYIMG, GAMEOVER
};
enum class SOUNDTYPE
{
	HIT, POINT, WING, END
};

class Pipe; class Land; class Bird; class Flash; class Hud;
class GameScene : public Scene
{
public:
	GameScene(std::shared_ptr<GameData> _data);
	~GameScene();
	void Init();
	void Update(float _dt);
	void Render();
private:
	std::shared_ptr<GameData> m_gameData;
	sf::Sound m_Sound[(int)SOUNDTYPE::END];
	sf::Sprite m_background;
	sf::Clock m_clock;
	Land* m_pLand;
	Pipe* m_pPipe;
	Bird* m_pBird;
	Flash* m_pFlash;
	Hud* m_pHud;
	GAMESTATE m_gameState;
	Collision m_collision;
	int m_iScore;
	int m_temphighscore;
	bool ishighScore;
};

