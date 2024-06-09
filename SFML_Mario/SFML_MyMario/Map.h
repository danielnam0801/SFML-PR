#pragma once
#include "tileson.hpp"
class Map
{
public:
	Map();
	~Map();
public:
	void CreateFromImage(const sf::Image& _image);
	void CreateJsonBoard();
	sf::Sprite* StoreAndLoadImage(const std::string& _image
								,const sf::Vector2f& _pos);
	void Render();
	void RenderLayer(tson::Layer& _layer);
	void RenderTileLayer(tson::Layer& _layer);
	void UpdateTileAnimation(float _dt);
private:
	std::vector<std::vector<int>> m_grid;
	float m_cellSize;
	tson::Tileson m_tson;
	std::unique_ptr<tson::Map> m_uptrMap;
	std::map<std::string, std::unique_ptr<sf::Texture>> m_maptex;
	std::map<std::string, std::unique_ptr<sf::Sprite>> m_mapsprite;
	tson::Map* m_curMap;
	std::map <std::string, std::unique_ptr<tson::Map>> m_maps;
	std::map<UINT, tson::Animation*> m_maptsonAnim;
};

