#include "pch.h"
#include "Gun.h"
#include "Bullet.h"

Gun::Gun(Player* player)
	: m_ownerplayer(player)
{
	Init();
}

Gun::~Gun()
{
	m_ownerplayer = nullptr;
}

void Gun::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
}

bool Gun::Shooting()
{
	if (m_clock.getElapsedTime().asSeconds() > m_cooltime)
	{
		m_clock.restart();
		m_bullet.push_back(new Bullet(m_sprite.getPosition()));
		return true;
	}
}
