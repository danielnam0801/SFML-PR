#include "pch.h"
#include "MyAnimation.h"
#include "Object.h"
#include "MyAnimator.h"
#include "WindowMgr.h"
void MyAnimation::Create(sf::Texture* _pTex, Vector2f _vLT, Vector2f _vSliceSize, Vector2f _vStep, UINT _iFrameCount, float _fDuration)
{
	m_pTex = _pTex;
	//m_sprite.setTexture(*_pTex);
	for (int i = 0; i < _iFrameCount; ++i)
	{
		sf::Texture tex;

		Sprite sprite;
		sprite.setTexture(*_pTex);
		//m_sprite.setTexture(*_pTex);
		//sprite.setTextureRect(sf::IntRect(sf::Vector2i(_vLT + _vStep * (float)i), sf::Vector2i(_vSliceSize)));
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * (float)i, _vSliceSize, {0.f,0.f},_fDuration
		,sprite }));
		//sf::Texture tex;
		//m_vecAnimation.push_back(Sprite(*_pTex, sf::IntRect(sf::Vector2i(_vLT + _vStep * (float)i), sf::Vector2i(_vSliceSize))));
		//m_vecAnimation.push_back();
	}
}

MyAnimation::MyAnimation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_fAccTime(0.f)
	, m_pTex(nullptr)
	, m_IsFinish(false)
{
}

MyAnimation::~MyAnimation()
{
}

void MyAnimation::Update(float _dt)
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
		return;
	m_fAccTime += _dt;
	// ������ �ð��� ���� �� �����ӿ� ������ �ð��� �Ѿ��.
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		// �ϴ� ���� �ð����� ���� ������ �ð��� ����..
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame; // �������� �������� �ѱ��
		if (m_CurFrame >= m_vecAnimFrame.size()) // �ѹ��� ��������
		{
			if (!m_pAnimator->GetRepeat())
				m_pAnimator->SetRepeatcnt();
			// �ʱ�ȭ
			m_CurFrame = 0;
			m_fAccTime = 0.f;
			//m_IsFinish = true;
		}
	}
	/*m_sprite = m_vecAnimFrame[m_CurFrame].sprite;
	Vector2f pos = m_pAnimator->GetObj()->GetPos();
	m_sprite.setPosition(pos);*/

	//m_sprite.setTextureRect(sf::IntRect((sf::Vector2i)(m_vecAnimFrame[m_CurFrame].vLT),
	//	(sf::Vector2i)(m_vecAnimFrame[m_CurFrame].vSlice)));



	// ����
	m_sprite.setTexture(*m_pTex);
	m_sprite.setTextureRect(sf::IntRect(m_vecAnimFrame[m_CurFrame].vLT.x, m_vecAnimFrame[m_CurFrame].vLT.y
		, m_vecAnimFrame[m_CurFrame].vSlice.x, m_vecAnimFrame[m_CurFrame].vSlice.y));
	Vector2f pos = m_pAnimator->GetObj()->GetPos();
	m_sprite.setPosition(m_pAnimator->GetObj()->GetPos());
	m_sprite.setScale(Vector2f(1.f, 1.f));
	m_pAnimator->GetObj()->SetSprite(m_sprite);

	// ����
	//m_sprite.setTexture(*m_pTex);
	//m_sprite.setTextureRect(sf::IntRect(m_vecAnimFrame[m_CurFrame].vLT.x, m_vecAnimFrame[m_CurFrame].vLT.y
	//	, m_vecAnimFrame[m_CurFrame].vSlice.x, m_vecAnimFrame[m_CurFrame].vSlice.y));
	//const Texture* tex = m_sprite.getTexture();
	//m_pAnimator->GetObj()->SetTexture(tex);


}

void MyAnimation::Render()
{

	//GET_WINDOW.draw(m_pAnimator->GetObj()->GetSprite());
}
