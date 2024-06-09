#include "pch.h"
#include "MyAnimator.h"
#include "MyAnimation.h"
MyAnimator::MyAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_IsRepeat(false)
{
}

MyAnimator::~MyAnimator()
{
	map<string, MyAnimation*>::iterator iter;
	for (iter = m_mapAnim.begin(); iter != m_mapAnim.end(); ++iter)
	{
		if (iter->second != nullptr)
			delete iter->second;
	}
	m_mapAnim.clear();
}

void MyAnimator::Render()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Render();
	}
}

void MyAnimator::CreateAnim(const string& _strName, sf::Texture* _pTex, Vector2f _vLT, Vector2f _vSliceSize, Vector2f _vStep, UINT _FrameCount, float _duration)
{
	MyAnimation* pAnim = FindAnim(_strName);
	// 잘 찾았으면 그냥 return
	if (pAnim != nullptr)
		return;
	//assert(pAnim==nullptr); // nullptr이면 지나가.
	//assert(pAnim); // 있으면 지나가 없으면 걸려
	pAnim = new MyAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _FrameCount, _duration);
	m_mapAnim.insert({ _strName,pAnim });
}

MyAnimation* MyAnimator::FindAnim(const string& _strName)
{
	map<string, MyAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
		return nullptr;
	return iter->second;
}

void MyAnimator::PlayAnim(const string& _strName, bool _IsRepeat, int _repeatcnt)
{
	m_pCurAnim = FindAnim(_strName);
	m_IsRepeat = _IsRepeat;
	m_repeatcnt = _repeatcnt;
}

void MyAnimator::Update(float _dt)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update(_dt);
	}
}
