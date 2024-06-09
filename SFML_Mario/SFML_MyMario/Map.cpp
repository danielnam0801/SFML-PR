#include "pch.h"
#include "Map.h"
#include "Object.h"
#include "Tile.h"
#include "Collider.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "tileson.hpp"
#include "DefTile.h"
#include "WindowMgr.h"
#include "Goomba.h"
#include "Ground.h"
#include "Pipe.h"
#include "brick.h"
Map::Map()
	: m_cellSize(16.f)
{
	// .c .h => c언어
	// .cpp .hpp => c++
	//tson::Tileson m_tson;
	m_uptrMap = m_tson.parse(fs::path("./Map/FinalStage5.json"));
	if (m_uptrMap->getStatus() != tson::ParseStatus::OK)
		std::cout << "json file error " << std::endl;
}

Map::~Map()
{
}

//void Map::CreateFromImage(const sf::Image & _image)
//{
//	// 깨끗하게 지워주고
//	m_grid.clear();
//	m_grid = std::vector(_image.getSize().x, 
//		std::vector(_image.getSize().y, 0));
//
//	sf::Vector2f mariopos;
//	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
//	for (size_t i = 0; i < m_grid.size(); ++i)
//	{
//		for (size_t j = 0; j < m_grid[i].size(); ++j)
//		{
//			if (_image.getPixel(i, j) == sf::Color::Black)
//			{
//				m_grid[i][j] = 1;
//				Object* pTile = new Tile(
//					Vector2f(i * m_cellSize,
//						j * m_cellSize)
//					, Vector2f(m_cellSize, m_cellSize));
//				pTile->SetName("Tile");
//				pCurScene->AddObject(pTile, OBJECT_GROUP::TILE);
//			}
//			else if (_image.getPixel(i, j) == sf::Color::Red)
//			{
//				mariopos = Vector2f(i * m_cellSize, j * m_cellSize);
//
//				Object* pPlayer = new Player;
//				pPlayer->SetName("Mario");
//				pPlayer->GetSprite().setPosition(mariopos);
//				pCurScene->AddObject(pPlayer, OBJECT_GROUP::PLAYER);
//			}
//		}
//	}
//}

void Map::CreateJsonBoard()
{
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();

	if (m_uptrMap->getStatus() == tson::ParseStatus::OK)
	{
		int a = 0;
		tson::Layer* tileLayer = m_uptrMap->getLayer("Tile Layer 1");
		//tson::Layer* tileLayer = m_uptrMap->getLayer("Ground");
		tson::Layer* ObjLayer = m_uptrMap->getLayer("Object Layer 1");
		if (ObjLayer->getName() == "Mario")
		{

		}
		//tson::Object* mario = ObjLayer->firstObj("Mario");
		for (auto& obj : ObjLayer->getObjects())
		{
			tson::Vector2i pos = obj.getPosition();
			if (obj.getName() == "Mario")
			{
				// 마리오 세팅
				Object* pObj = new Player(Vector2f(pos.x, pos.y));
				pObj->SetName("Mario");
				pCurScene->AddObject(pObj, OBJECT_GROUP::PLAYER);
			}
			else if (obj.getName() == "Goomba")
			{
				// 마리오 세팅
				Object* pObj = new Goomba(Vector2f(pos.x, pos.y));
				pObj->SetName("Goomba");
				pCurScene->AddObject(pObj, OBJECT_GROUP::MONSTER);
			}
		}
		for (auto& [pos, tileObject] : m_uptrMap->getLayer("Ground")->getTileObjects())
		{
			tson::Tileset* tileset = tileObject.getTile()->getTileset();
			tson::Rect rect = tileObject.getDrawingRect();
			tson::Vector2f realpostion = tileObject.getPosition();
			sf::Sprite* sprite = StoreAndLoadImage(tileset->getImage().u8string(),{0,0});
			if (sprite != nullptr)
			{
				sprite->setTextureRect({ rect.x, rect.y, rect.width,rect.height});
				sprite->setPosition({ realpostion.x, realpostion.y});
				// 그라운드 라는 클래스를 파서 오브젝트에 추가합니다.
				Object* pObj = new Ground(*sprite);
				pObj->SetName("Ground");
				pCurScene->AddObject(pObj, OBJECT_GROUP::GROUND);
			}
		}
		for (auto& [pos, tileObject] : m_uptrMap->getLayer("broke brick")->getTileObjects())
		{
			tson::Tileset* tileset = tileObject.getTile()->getTileset();
			tson::Rect rect = tileObject.getDrawingRect();
			tson::Vector2f realpostion = tileObject.getPosition();
			sf::Sprite* sprite = StoreAndLoadImage(tileset->getImage().u8string(), { 0,0 });
			if (sprite != nullptr)
			{
				sprite->setTextureRect({ rect.x, rect.y, rect.width,rect.height });
				sprite->setPosition({ realpostion.x, realpostion.y });
				// 그라운드 라는 클래스를 파서 오브젝트에 추가합니다.
				Object* pObj = new Brick(*sprite);
				pObj->SetName("Brick");
				pCurScene->AddObject(pObj, OBJECT_GROUP::GROUND);
			}
		}
		for (auto& [pos, tileObject] : m_uptrMap->getLayer("pipe")->getTileObjects())
		{
			tson::Tileset* tileset = tileObject.getTile()->getTileset();
			tson::Rect rect = tileObject.getDrawingRect();
			tson::Vector2f realpostion = tileObject.getPosition();
			sf::Sprite* sprite = StoreAndLoadImage(tileset->getImage().u8string(), { 0,0 });
			if (sprite != nullptr)
			{
				sprite->setTextureRect({ rect.x, rect.y, rect.width,rect.height });
				sprite->setPosition({ realpostion.x, realpostion.y });
				// 그라운드 라는 클래스를 파서 오브젝트에 추가합니다.
				Object* pObj = new Pipe(*sprite);
				pObj->SetName("pipe");
				pCurScene->AddObject(pObj, OBJECT_GROUP::PIPE);
			}
		}

		/*if (tileLayer->getType() == tson::LayerType::TileLayer)
		{
			for (auto& [pos, tileobject] : tileLayer->getTileObjects())
			{
				tson::Tileset* tileset = tileobject.getTile()->getTileset();
				tson::Rect drawingRect = tileobject.getDrawingRect();
				tson::Vector2f position = tileobject.getPosition();
				tson::Vector2i imagesize = tileset->getImageSize();
				sf::Sprite* sprite = StoreAndLoadImage(tileset->getImage().generic_u8string(), { 0,0 });
				if (nullptr != sprite)
				{
					sprite->setTextureRect({drawingRect.x, drawingRect.y,drawingRect.width, drawingRect.height});
					sprite->setPosition({ position.x,position.y});
					Object* pobj = new DefTile(*sprite);
					pobj->SetName("DefTile");
					SceneMgr::GetInst()->GetCurScene()->AddObject(pobj,OBJECT_GROUP::TILE);
				}
			}
		}*/
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
			std::cout << "can't find" << path.generic_string() << std::endl;

	}
	if (m_mapsprite.count(_image) > 0)
		return m_mapsprite[_image].get();
	return nullptr;
}

void Map::Render()
{
	m_curMap = m_uptrMap.get();
	//m_curMap = m_maps["stage2"].get();
	if (m_curMap != nullptr)
	{
		for (auto& layer : m_curMap->getLayers())
			RenderLayer(layer);
	}
}

void Map::RenderLayer(tson::Layer& _layer)
{
	switch (_layer.getType())
	{
	case tson::LayerType::TileLayer:
		RenderTileLayer(_layer);
		break;
	case tson::LayerType::ObjectGroup:
		break;
	case tson::LayerType::ImageLayer:
		break;
	default:
		break;
	}
}

void Map::RenderTileLayer(tson::Layer& _layer)
{
	// pos: 실제 pos가 아님. 타일 단위의 pos라고 생각하면 됨.
	for (auto& [pos, tileobject] : _layer.getTileObjects())
	{
		// tileget한거의 tileset을 가져온다.
		tson::Tileset* tileset = tileobject.getTile()->getTileset();
		tson::Rect drawingRect;
		bool IsAnimation = tileobject.getTile()->getAnimation().any();
		if (!IsAnimation)
			drawingRect = tileobject.getDrawingRect();
		else // 애니메이션이 있는 타일이다.
		{
			UINT tileID = tileobject.getTile()->getId();

			// 애니메이션 담는거야.
			if (m_maptsonAnim.count(tileID) == 0)
				m_maptsonAnim[tileID] = &tileobject.getTile()->getAnimation();

			//if (tileobject.getTile()->getAnimation().any())
			if(IsAnimation)
			{
				UINT curID = tileobject.getTile()->getAnimation().getCurrentTileId();
				tson::Tile* animationtile;
				UINT tempID;
				for (auto& [id, animation] : m_maptsonAnim)
				{
					tempID = animation->getCurrentTileId();
					if (tempID)
						break;
				}
				/*for (auto& [id, animation] : m_tsonMapAnimation)
				{
					std::cout << "Frame: " << animation->getCurrentFrameNumber() << "Duration: " << animation->getCurrentFrame()->getDuration()
						<< "Tile: " << animation->getCurrentTileId() << std::endl;
					ID = animation->getCurrentTileId();
					if (ID)
						break;
				}*/
				animationtile = tileset->getTile(1);
				drawingRect = animationtile->getDrawingRect();
			}

		}
		tson::Vector2f position = tileobject.getPosition();
		tson::Vector2i imagesize = tileset->getImageSize();
		sf::Sprite* sprite = StoreAndLoadImage(tileset->getImage().generic_u8string(), { 0,0 });
		if (nullptr != sprite)
		{
			tson::Animation ani = tileobject.getTile()->getAnimation();
			if (ani.any())
			{
				static int framelt = 0;
				if (framelt > ani.getFrames().size()) framelt = 0;
				sprite->setTextureRect({ drawingRect.x + framelt * tileobject.getTile()->getTileSize().x, 
					drawingRect.y,drawingRect.width, drawingRect.height});
				framelt++;
			}
			else
			// texture 입히기.
				sprite->setTextureRect({ drawingRect.x, drawingRect.y,drawingRect.width, drawingRect.height });

			// origin 설정
			sf::Vector2f origin{ (float)(drawingRect.width / 2), (float)(drawingRect.height / 2) };
			sprite->setOrigin(origin);

			position = {position.x + origin.x, position.y + origin.y};
			// 포지션 잡기.
			sprite->setPosition({ position.x,position.y });
			
			GET_WINDOW.draw(*sprite);
			//// 크기 설정
			//sf::Vector2f scale = sprite->getScale();
			//sprite->setScale(scale);

			//Object* pobj = new DefTile(*sprite);
			//pobj->SetName("DefTile");
			//SceneMgr::GetInst()->GetCurScene()->AddObject(pobj, OBJECT_GROUP::TILE);
		}
	}
	
}

void Map::UpdateTileAnimation(float _dt)
{
	for(auto& [id, animation] : m_maptsonAnim)
	{
		animation->update(_dt / 1000);
	}
}
