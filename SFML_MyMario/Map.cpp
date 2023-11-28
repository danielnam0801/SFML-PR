#include "pch.h"
#include "Map.h"
#include "Object.h"
#include "Tile.h"
#include "Collider.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
Map::Map()
	: m_cellSize(16.f)
{
}

Map::~Map()
{
}

void Map::CreateFromImage(const sf::Image & _image)
{
	// ±ú²ýÇÏ°Ô Áö¿öÁÖ°í
	m_grid.clear();
	m_grid = std::vector(_image.getSize().x, 
		std::vector(_image.getSize().y, 0));

	sf::Vector2f mariopos;
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
	for (size_t i = 0; i < m_grid.size(); ++i)
	{
		for (size_t j = 0; j < m_grid[i].size(); ++j)
		{
			if (_image.getPixel(i, j) == sf::Color::Black)
			{
				m_grid[i][j] = 1;
				Object* pTile = new Tile(
					Vector2f(i * m_cellSize,
						j * m_cellSize)
					, Vector2f(m_cellSize, m_cellSize));
				pTile->SetName("Tile");
				pCurScene->AddObject(pTile, OBJECT_GROUP::TILE);
			}
			else if (_image.getPixel(i, j) == sf::Color::Red)
			{
				mariopos = Vector2f(i * m_cellSize, j * m_cellSize);

				Object* pPlayer = new Player;
				pPlayer->SetName("Mario");
				pPlayer->GetSprite().setPosition(mariopos);
				pCurScene->AddObject(pPlayer, OBJECT_GROUP::PLAYER);
			}
		}
	}
}
