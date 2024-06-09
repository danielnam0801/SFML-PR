#pragma once
#include "Scene.h"
#include "Core.h"
#include "Collision.h"
enum class GAMESTATE
{
	IDLE, PLAYING, GAMEOVER
};
enum class SOUNDTYPE
{
	HIT, POINT, WING, END
};
class Pipe; class Land; class Bird;
class Flash; class Hud;
class GameScene : public Scene
{
public:
	GameScene(std::shared_ptr<GameData> _data);
	~GameScene();
	void Init();
	void Update(float _dt);
	void Render();
private:
	sf::Sound m_Sound[(int)SOUNDTYPE::END];
	std::shared_ptr<GameData> m_gamedata;
	sf::Sprite m_background;
	Pipe* m_pPipe;
	Land* m_pLand;
	Bird* m_pBird;
	Flash* m_pFlash;
	Hud* m_pHud;
	sf::Clock m_clock;
	GAMESTATE m_eGameState;
	Collision m_collision;
	int		  m_Score;
	int		  m_temphighscore;
	bool      m_isHigh;
};

