#pragma once
class Map
{
public:
	Map();
	~Map();
public:
	void GreateFromImage(const sf::Image& _image);
private:
	std::vector<std::vector<int>> m_grid;
	float m_cellsize;
	
};

