#include "pch.h"
#include "Camera.h"

sf::View Camera::GetWindowView(sf::Vector2u _windowsize)
{
	float ratio = (float)_windowsize.x / (float)_windowsize.y;
	
	sf::Vector2f size{};
	if (ratio < 1.f) // 세로가 더큼.
	{
		size = sf::Vector2f(m_zoomlevel, m_zoomlevel / ratio);
	}
	else // 가로가 더큼.
	{
		size = sf::Vector2f(m_zoomlevel * ratio, m_zoomlevel);
	}
	return sf::View(m_pos, size);
}
