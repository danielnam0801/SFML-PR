#include "pch.h"
#include "FrontGun.h"
#include "Player.h"
void FrontGun::Init()
{
	m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Front Gun"));
	m_sprite.setPosition(m_ownerplayer->GetSprite().getPosition());
}
