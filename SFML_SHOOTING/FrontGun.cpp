#include "pch.h"
#include "FrontGun.h"
#include "Player.h"

void FrontGun::Init()
{
	m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Gun0"));
	m_sprite.setPosition(Vector2f{
		m_ownerplayer->GetSprite().getGlobalBounds().width/2,
		m_ownerplayer->GetSprite().getGlobalBounds().height
	});
}

void FrontGun::Update()
{
}
