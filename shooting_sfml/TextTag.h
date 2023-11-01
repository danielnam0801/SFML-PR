#pragma once
class TextTag
{
public:
	TextTag(std::string _text, float _timer, float _fSpeed, 
		Vector2f _pos, Vector2f _dir, Color _color, int _size
		,bool _acc);
	~TextTag();
public:
	void Update(const float& _dt);
	void Render();
	void SetText(std::string _text, Vector2f _pos);
public:
	const bool& GetIsErase() const { return m_IsErase; }
private:
	sf::Text m_text;
	sf::Clock m_clock;
	float m_timer;
	float m_fSpeed;
	Vector2f m_dir;
	bool m_IsErase;
	bool m_IsAcc;
};

