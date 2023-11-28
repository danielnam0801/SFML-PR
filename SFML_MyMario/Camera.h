#pragma once
class Camera
{
	SINGLE(Camera);
public:
	sf::View GetWindowView(sf::Vector2u _windowsize);
	sf::View& GetMainCam()
	{
		return m_maincam;
	}
	sf::Vector2f& GetPos()
	{
		return m_pos;
	}
	void SetPos(Vector2f _pos)
	{
		m_pos = _pos;
	}
	void SetZoomLevel(float _f) { m_zoomlevel = _f; }
private:
	sf::View m_maincam;
	Vector2f m_pos;
	float m_zoomlevel;
};

