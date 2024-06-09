#include "pch.h"
#include "TextTag.h"
#include "ResMgr.h"
TextTag::TextTag(std::string _text, float _timer, float _fSpeed, Vector2f _pos, Vector2f _dir, Color _color, int _size, bool _acc)
{
	m_text.setFont(ResMgr::GetInst()->GetFont("Dosis Font"));
	m_text.setCharacterSize(_size);
	m_text.setPosition(_pos);
	m_text.setFillColor(_color);
	m_text.setString(_text);
	m_fSpeed = _fSpeed;
	m_dir = _dir;
	m_timer = _timer;
	m_IsAcc = _acc;
	m_IsErase = false;
}
TextTag::~TextTag()
{
}

void TextTag::Update(const float& _dt)
{
	if (m_IsAcc)
	{
		if(m_clock.getElapsedTime().asSeconds() > m_timer / 2)
			m_text.move(m_dir * _dt * m_fSpeed * 3.f);
		else
			m_text.move(m_dir * _dt * m_fSpeed);
	}
	else
		m_text.move(m_dir * _dt * m_fSpeed);

	if (m_clock.getElapsedTime().asSeconds() > m_timer)
	{
		// todo: iserase 시킨거 삭제하자!!
		m_IsErase = true;
		m_text.setFillColor(Color(0,0,0,0));
		m_clock.restart();
	}
}

void TextTag::Render()
{
	WindowMgr::GetInst()->GetWindow().draw(m_text);
}

void TextTag::SetText(std::string _text, Vector2f _pos)
{
}
