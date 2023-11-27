#include "pch.h"
#include "Tile.h"
#include "WindowMgr.h"

Tile::Tile(Vector2f _pos, Vector2f _scale)
{
	m_sprite.setPosition(_pos);
	m_sprite.setPosition(_scale);
}

void Tile::Update(float _dt)
{
	m_sprite.getPosition();
	m_sprite.setPosition();
}

void Tile::Render()
{
	GET_WINDOW.draw(m_sprite);
}
