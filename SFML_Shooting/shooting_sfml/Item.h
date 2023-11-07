#pragma once
class Item
{
public:
	Item(Vector2f _pos, Vector2f _dir,
		ITEMTYPE _eType, float _aliveTime);
	void Update();
	void Render();
private:
	Sprite m_sprite;
	ITEMTYPE m_eType;
	Vector2f m_dir;
	float m_alivetimer;
	float m_alivetimermax;

};

