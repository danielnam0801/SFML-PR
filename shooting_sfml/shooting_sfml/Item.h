#pragma once
class Item
{
public:
	Item(Vector2f _pos, Vector2f _dir, 
		ITEM_TYPE _etype, float _alivetime);
	void Update(const float& _dt);
	void Render();
private:
	Sprite m_sprite;
	ITEM_TYPE m_eType;
	Vector2f m_dir;
	float m_alivetimer;
	float m_alivetimermax;
};
