#include "pch.h"
#include "Map.h"
#include "Object.h"
#include "Tile.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Scene.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::GreateFromImage(const sf::Image& _image)
{
	m_grid.clear();
	m_grid = std::vector(_image.getSize().x,
		std::vector(_image.getSize().y, 0));
	
	sf::Vector2f marioPos;
	std::shared_ptr<Scene> p_CurScene = SceneMgr::GetInst()->GetCurScene();

	for (size_t i = 0; i < m_grid.size(); ++i)
	{
		for (size_t j = 0; j < m_grid[i].size(); ++j)
		{
			if (_image.getPixel(i, j) == sf::Color::Black)
			{
				m_grid[i][j] = 1;
				Object* pTile = new Tile(
					Vector2f(i * m_cellsize, j * m_cellsize),
					Vector2f(m_cellsize, m_cellsize)
				);
				pTile->SetName("TIle");
				p_CurScene->
					AddObject(pTile, OBJECT_GROUP::TILE);
			}
			else if (_image.getPixel(i, j) == sf::Color::Red)
			{
				marioPos = Vector2f(i * m_cellsize, j * m_cellsize);
				Object* pPlayer = new Player;
				pPlayer->SetName("Mario");
				pPlayer->GetSprite().setPosition(marioPos);
				p_CurScene->AddObject(pPlayer, OBJECT_GROUP::PLAYER);
			}
;		}
	}
}
