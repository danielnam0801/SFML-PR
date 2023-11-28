#include "pch.h"
#include "Camera.h"

sf::View Camera::GetWindowView(sf::Vector2u _windowsize)
{
	float ratio = (float)_windowsize.x / (float)_windowsize.y;
	
	sf::Vector2f size{};
	if (ratio < 1.f) // ���ΰ� ��ŭ.
	{
		size = sf::Vector2f(m_zoomlevel, m_zoomlevel / ratio);
	}
	else // ���ΰ� ��ŭ.
	{
		size = sf::Vector2f(m_zoomlevel * ratio, m_zoomlevel);
	}
	return sf::View(m_pos, size);
}
