#pragma once
#include "Scene.h"
#include "Core.h"
#include "Collision.h"
enum class GAMESTATE
{
	IDLE, PLAYIMG, GAMEOVER
};
class Pipe; class Land; class Bird; class Flash;
class GameScene : public Scene
{
public:
	GameScene(std::shared_ptr<GameData> _data);
	~GameScene();
	void Init();
	void Update(float _dt);
	void Render();
	void RenderScore();
private:
	std::shared_ptr<GameData> m_gameData;
	sf::Sprite m_background;
	sf::Text m_text;
	sf::Font m_font;

	Land* m_pLand;
	Pipe* m_pPipe;
	Bird* m_pBird;
	Flash* m_pFlash;
	GAMESTATE m_gameState;
	Collision m_collision;
	int m_iScore;
};

