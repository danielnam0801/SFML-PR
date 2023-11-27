#pragma once
#include "Object.h"
class Tile : public Object
{
public:
	Tile(Vector2f _pos, Vector2f _scale);
public:
	void Update(float _dt);
	void Render();
private:
	Sprite m_sprite;
};

