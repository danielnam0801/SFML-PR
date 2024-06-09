#pragma once
//enum class AnimType { manual, forward, forward_stop, forward_cycle, forward_backward_cycle };
class Object;
class MyAnimation;
class MyAnimator
{
public:
	const bool& GetRepeat() const { return m_IsRepeat; }
	const int& GetRepeatcnt() const { return m_repeatcnt; }
	void SetRepeatcnt() { --m_repeatcnt; }
private:
	bool m_IsRepeat;
	int  m_repeatcnt;
public:
	Object* GetObj() const { return m_pOwner; }
public:
	MyAnimator();
	~MyAnimator();
public:
	void Render();
	void CreateAnim(const string& _strName, Texture* _pTex, Vector2f _vLT
		, Vector2f _vSliceSize, Vector2f _vStep, UINT _FrameCount, float _duration);
	MyAnimation* FindAnim(const string& _strName);
	void PlayAnim(const string& _strName, bool _IsRepeat, int _repeatcnt = 1);
private:
	map<string, MyAnimation*> m_mapAnim;
	MyAnimation* m_pCurAnim; // ÇöÀç anim
public:
	void Update(float _dt);

private:
	Object* m_pOwner;
	friend class Object;
};


