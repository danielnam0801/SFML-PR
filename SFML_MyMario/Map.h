#pragma once
class Map
{
public:
	Map();
	~Map();
public:
	void CreateFromImage(const sf::Image& _image);
private:
	std::vector<std::vector<int>> m_grid;
	float m_cellSize;
};

