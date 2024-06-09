#pragma once
class MyAnimator;
struct tAnimFrame
{
	Vector2f vLT;
	Vector2f vSlice;
	Vector2f vOffset;
	float fDuration;
	sf::Sprite sprite;
};
class MyAnimation
{
public:
	const size_t& GetMaxFrame() { return m_vecAnimFrame.size(); }
	void SetFrameOffset(int _index, Vector2f _offset) { m_vecAnimFrame[_index].vOffset = _offset; }
	tAnimFrame& GetFrame(int _index) { return m_vecAnimFrame[_index]; }
private:
	UINT	m_CurFrame;
	float   m_fAccTime; // 누적 시간
	int     m_repeatcnt; // 반복 횟수
public:
	void SetFrame(int _frame)
	{
		m_CurFrame = _frame;
		m_IsFinish = false;
		m_fAccTime = 0.f;
	}
	const bool& IsFinish() const { return m_IsFinish; }
	bool	m_IsFinish; // 끝났는지
public:
	void Create(sf::Texture* _pTex, Vector2f _vLT, Vector2f _vSliceSize,
		Vector2f _vStep, UINT _iFrameCount, float _fDuration);
private:
	sf::Texture* m_pTex; // 애니메이션 텍스처
	sf::Sprite m_sprite;
	vector<tAnimFrame> m_vecAnimFrame;
	vector<sf::Sprite> m_vecAnimation;

public:
	MyAnimation();
	~MyAnimation();
public:
	void Update(float _dt);
	void Render();
	friend class MyAnimator;
public:
	void SetName(const string& _strName)
	{
		m_strName = _strName;
	}
	const string& GetName() { return m_strName; }
private:
	string m_strName;
	MyAnimator* m_pAnimator;

};

