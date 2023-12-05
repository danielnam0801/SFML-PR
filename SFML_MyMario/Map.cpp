#include "pch.h"
#include "Map.h"
#include "Object.h"
#include "Tile.h"
#include "Collider.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "DefTile.h"
#include "tileson.hpp"
#include "WindowMgr.h"

Map::Map()
	: m_cellSize(16.f)
{
	m_uptrMap = m_tson.parse(fs::path("./Map/FinalStage3 (1).json"));
	if (m_uptrMap->getStatus() != tson::ParseStatus::OK)
	{
		std::cout << "json file error " << std::endl;
	}
}

Map::~Map()
{
}

void Map::CreateFromImage(const sf::Image & _image)
{
	// 깨끗하게 지워주고
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

void Map::CreateJsonBoard()
{
	if (m_uptrMap->getStatus() == tson::ParseStatus::OK)
	{
		int a = 0;
		tson::Layer* tileLayer = m_uptrMap->getLayer("Ground");
		tson::Layer* objLayer = m_uptrMap->getLayer("Object Layer 1");
		if (objLayer->getName() == "Mario")
		{

		}

		for (auto& obj : objLayer->getObjects())
		{
			tson::Vector2i pos = obj.getPosition();
			if (obj.getName() == "Mario")
			{
				//마리오 세팅

			}
		}
		for (auto& [pos, tileObject] : m_uptrMap->getLayer("Ground")->getTileObjects())
		{
			tson::Tileset* tileset = tileObject.getTile()->getTileset();
			tson::Rect rect = tileObject.getDrawingRect();
			tson::Vector2f realposition = tileObject.getPosition();
			sf::Sprite* sprite = StoreAndLoadImage(tileset->getImage().u8string(), { 0,0 });
			if (sprite != nullptr)
			{
				sprite->setTextureRect({ rect.x, rect.y, rect.width, rect.height });
				sprite->setPosition({});
			}
		}
	}
}

sf::Sprite* Map::StoreAndLoadImage(const std::string& _image, const sf::Vector2f& _pos)
{
	fs::path path = _image;
	if (m_maptex.count(_image) == 0)
	{
		if (fs::exists(path) && fs::is_regular_file(path))
		{
			std::unique_ptr<sf::Texture> tex = std::make_unique<sf::Texture>();
			bool imageFound = tex->loadFromFile(path.generic_string());
			if (imageFound)
			{
				std::unique_ptr<sf::Sprite> spr = std::make_unique<sf::Sprite>();
				spr->setTexture(*tex);
				spr->setPosition(_pos);
				m_maptex[_image] = std::move(tex);
				m_mapsprite[_image] = std::move(spr);
			}
		}
		else
		{
			std::cout << "can't find" << path.generic_string() << std::endl;
		}
	}
	if (m_mapsprite.count(_image) > 0)
		return m_mapsprite[_image].get();
	return nullptr;
}

void Map::Render()
{
	m_curMap = m_uptrMap.get();
	if (m_curMap != nullptr)
	{
		for (auto& layer : m_curMap->getLayers())
			RenderLayers(layer);
	}
}

void Map::RenderLayers(tson::Layer& _layer)
{
	switch (_layer.getType())
	{
	case::tson::LayerType::TileLayer:
		RenderTileLayer(_layer);
		break;
	case::tson::LayerType::ObjectGroup:
		break;
	case::tson::LayerType::ImageLayer:
		break;
	default:
		break;
	}
}

void Map::RenderTileLayer(tson::Layer & _layer) {
	// 실제 포지션이 아닌 타일 단위의 포지션
	for (auto& [pos, tileObj] : _layer.getTileObjects()) {
		tson::Tileset* tileSet = tileObj.getTile()->getTileset();
		tson::Rect rect;

		bool isAnimation = tileObj.getTile()->getAnimation().any();
		if (!isAnimation) {
			rect = tileObj.getDrawingRect();
		}
		else {
			UINT tileId = tileObj.getTile()->getId();
			if (m_maptsonAnim.count(tileId) == 0) {
				m_maptsonAnim[tileId] = &tileObj.getTile()->getAnimation();
			}


			UINT curId = tileObj.getTile()->getAnimation().getCurrentTileId();
			tson::Tile* animationTile;
			for (auto& [id, animation] : m_maptsonAnim) {
				animationTile = tileSet->getTile(1);
				rect = animationTile->getDrawingRect();
			}

			for (auto& [id, animation] : m_maptsonAnim)
			{
				std::cout << "Frame: " << animation->getCurrentFrameNumber() << "Duration: " << animation->getCurrentFrame()->getDuration()
					<< "Tile: " << animation->getCurrentTileId() << std::endl;
				tileId = animation->getCurrentTileId();
				if (tileId)
					break;
			}
		}

		tson::Vector2f realPos = tileObj.getPosition();
		tson::Vector2i imageSize = tileSet->getImageSize();
		sf::Sprite* sprite = StoreAndLoadImage(tileSet->getImage().u8string(), { 0, 0 });

		if (sprite != nullptr) {
			tson::Animation ani = tileObj.getTile()->getAnimation();
			if (ani.any()) {
				static int frame = 0;
				if (frame > ani.getFrames().size()) {
					frame = 0;
				}
				sprite->setTextureRect({ rect.x + frame * tileObj.getTile()->getTileSize().x, rect.y, rect.width, rect.height });
				frame++;
			}

			// texture 입히기
			sprite->setTextureRect({ rect.x, rect.y, rect.width, rect.height });

			// origin 세팅
			sf::Vector2f  origin = { (float)rect.width / 2.f, (float)rect.height / 2.f };
			sprite->setOrigin(origin);

			// position 세팅
			realPos = { realPos.x + origin.x, realPos.y + origin.y };
			sprite->setPosition({ realPos.x, realPos.y });

			GET_WINDOW.draw(*sprite);
		}
	}
}

void Map::UpdateTileAnimation(float _dt)
{
	for (auto& [id, animation] : m_maptsonAnim)
	{
		animation->update(_dt*1000);
	}
}


