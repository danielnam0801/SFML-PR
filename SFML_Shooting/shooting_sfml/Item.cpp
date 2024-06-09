#include "pch.h"
#include "Item.h"

Item::Item(Vector2f _pos, Vector2f _dir, ITEM_TYPE _etype, float _alivetime)
{
	m_eType = _etype;
	switch (m_eType)
	{
	case ITEM_TYPE::HPKIT:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("HpKit"));
	}
		break;
	case ITEM_TYPE::STAT_POINT:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("StatPoint"));
	}
		break;
	case ITEM_TYPE::HPMAXUP:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Hptank"));
	}
		break;
	case ITEM_TYPE::DOUBLE:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Double"));
	}
		break;
	case ITEM_TYPE::TRIPLE:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Triple"));
	}
		break;
	case ITEM_TYPE::PIERCING:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Piercing"));
	}
		break;
	case ITEM_TYPE::SHIELD:
	{
		m_sprite.setTexture(ResMgr::GetInst()->GetTexture("Shield"));
	}
		break;
	}
	m_sprite.setColor(Color(255, 255, 255, 200));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
						m_sprite.getGlobalBounds().height / 2);
	m_alivetimermax = _alivetime;
	m_alivetimer = 0.f;
	m_sprite.setPosition(_pos);
	m_dir = _dir;
}

void Item::Update(const float& _dt)
{
	if (m_alivetimer < m_alivetimermax)
		m_alivetimer++;
	m_sprite.rotate(90.f * _dt);
	m_sprite.move(100.f * m_dir * _dt);
}

void Item::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_sprite);
}
