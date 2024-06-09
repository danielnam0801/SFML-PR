#include "pch.h"
#include "Tile.h"
#include "WindowMgr.h"
#include "ResMgr.h"
Tile::Tile(Vector2f _pos, Vector2f _scale)
{
	GetSprite().setTexture(ResMgr::GetInst()->GetTexture("brick"));
	GetSprite().setPosition(_pos);
	GetSprite().setScale(Vector2f(_scale.x / GetSprite().getTexture()->getSize().x,
								_scale.y / GetSprite().getTexture()->getSize().y));
}

void Tile::Update(float _dt)
{
	//m_sprite.getPosition();

	//m_sprite.setPosition();	
}

void Tile::Render()
{
	GET_WINDOW.draw(GetSprite());
}
