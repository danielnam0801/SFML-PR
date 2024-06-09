#include "pch.h"
#include "Player.h"
#include "Collider.h"
#include "ResMgr.h"
#include "WindowMgr.h"
#include "Camera.h"
#include "Rigidbody.h"
#include "MyAnimator.h"
#include "EventMgr.h"
//Player::Player()
//{
//	GetSprite().setTexture(ResMgr::GetInst()->GetTexture("idle"));
//	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
//						,GetSprite().getGlobalBounds().height / 2);
//	CreateRigidbody();
//}
Player::Player(sf::Vector2f _pos)
{
	m_jumpsound.setBuffer(ResMgr::GetInst()->GetSound("jump"));
	m_diesound.setBuffer(ResMgr::GetInst()->GetSound("mario_die"));
	m_tex = ResMgr::GetInst()->GetTexture("mario");
	//m_tex.loadFromFile("Texture\\mario.png");
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
		, GetSprite().getGlobalBounds().height / 2);

	GetSprite().setTexture(m_tex);
	GetSprite().setTextureRect(sf::Rect(210,0,15,15));
	GetSprite().setPosition(_pos);
	//SetScale(Vector2f(GetSprite().getGlobalBounds().width, GetSprite().getGlobalBounds().height));

	// collider
	CreateCollider();
	GetCollider()->SetScale(sf::Vector2f(GetSprite().getGlobalBounds().width,
		GetSprite().getGlobalBounds().height));
	GetCollider()->SetPos(GetSprite().getPosition());
	//GetCollider()->SetOffsetPos(Vector2f(0.f, 10.f));
	// animator
	CreateAnimator();
	GetAnimator()->CreateAnim("marioRight", &m_tex, Vector2f(240.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 3, 0.2f);
	GetAnimator()->CreateAnim("marioLeft", &m_tex, Vector2f(150.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(-30.f, 0.f), 3, 0.2f);
	GetAnimator()->CreateAnim("marioIdleRight", &m_tex, Vector2f(210.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("marioIdleLeft", &m_tex, Vector2f(180.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("marioJumpLeft", &m_tex, Vector2f(30.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("marioJumpRight", &m_tex, Vector2f(360.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("marioRightStop", &m_tex, Vector2f(360.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("marioLeftStop", &m_tex, Vector2f(360.f, 0.f),
		Vector2f(15.f, 15.f), Vector2f(30.f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim("mariodie", &m_tex, Vector2f(390.f, 0.f),
		Vector2f(15.f, 30.f), Vector2f(30.f, 0.f), 1, 0.2f);

	// rigidbody
	CreateRigidbody();

	//m_dir = Vector2f(1.f, 0.f);
	SetDir(Vector2f(1.f, 0.f));
	m_eCurState = MARIO_STATE::IDLE;
	SetGravity(true);
}
void Player::Update(float _dt)
{
	Vector2f camerapos = Camera::GetInst()->GetMainCam().getCenter();
	camerapos = GetPos();
	camerapos.y -= SCREEN_HEIGHT / 8.f;
	Camera::GetInst()->GetMainCam().setCenter(camerapos);
	// 움직임
	MoveUpdate(_dt);
	GetRigidbody()->SetGravity(Vector2f(0.f, 800.f));
	// 상태 변경
	StateUpdate(_dt);
	// 애니메이션 변경
	AnimationUpdate(_dt);
	GetAnimator()->Update(_dt);	
	// 가장 마지막에 하자. 왜냐하면, 상태 바뀌었을때 위에서 인지할거고
	// 이후 다음 프레임에서 체크할 수 있다. 피격상태가 되었을때
	// 다음 프레임에서 예외처리 같은거 할 수 있다.
	m_ePrevState = m_eCurState;
	SetPrevDir(GetDir());
}

void Player::Render()
{
	GET_WINDOW.draw(GetSprite());
	Component_Render();
}

void Player::EnterCollision(Collider* _pOther)
{
	Object* pOtherobj = _pOther->GetObj();
	if (pOtherobj->GetName() == "Ground")
	{
		Vector2f pos = GetPos();
		// 마리오가 땅보다 위로가면 IDLE
		if (pos.y < pOtherobj->GetPos().y)
		{
			m_eCurState = MARIO_STATE::IDLE;
		}
		//SetGround(true);
		//if (IsGround())
		//{
		//	// 경직
		//	//pObj->GetRigidbody()->SetVelocity(Vector2f(0.f, 0.f));

		//	// 원래
		//	Vector2f velocity =GetRigidbody()->GetVelocity();
		//	GetRigidbody()->SetVelocity(Vector2f(velocity.x, 0.f));
		//}
		//Vector2f vObjPos = _pOther->GetFinalPos();
		//Vector2f vObjScale = _pOther->GetScale();

		//Vector2f vPos = GetCollider()->GetFinalPos();
		//Vector2f vScale = GetCollider()->GetScale();
		//float fLen = abs(vObjPos.y - vPos.y);
		//float fValue = (vObjScale.y / 3.f + vScale.y / 3.f) - fLen;
		//vObjPos = GetPos();
		////vObjPos.y -= (fValue -1.f); // 1픽셀 더 밀어서 달달달 안거리게
		//vObjPos.y -= (fValue); // 1픽셀 더 밀어서 달달달 안거리게
		//SetPos(vObjPos);
	}
}

void Player::ExitCollision(Collider* _pOther)
{
}

void Player::StayCollision(Collider* _pOther)
{
}

void Player::MoveUpdate(float _dt)
{
	Rigidbody* pRigidbody = GetRigidbody();
	//Vector2f vPos = GetPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		pRigidbody->AddForce(Vector2f(-200.f,0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		pRigidbody->AddForce(Vector2f(200.f,0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_ePrevState != MARIO_STATE::JUMP)
		//&& m_eCurState !=MARIO_STATE::DOWN && m_eCurState !=MARIO_STATE::WALK)
	{
		m_jumpsound.play();
		m_eCurState = MARIO_STATE::JUMP;
		//m_acctime += _dt;
		SetDir(Vector2f(GetDir().x, -1.f));
		if (GetRigidbody())
		{
			//pRigid->AddForce(Vector2f(0.f, -400.f));

			// 기존
			//pRigidbody->AddVelocity(Vector2f(0.f, -50.f));

			// 개선 2단점프
			pRigidbody->SetVelocity(Vector2f(pRigidbody->GetVelocity().x, -600.f));

		}
		SetGround(false);
	}
	//GetSprite().setPosition(vPos);
}

void Player::StateUpdate(float _dt)
{
	if (GetIsDead())
		m_eCurState = MARIO_STATE::DIE;
	// 이동건드릴때 상태, 상태건드릴때 이동 안건드릴수있음.
	// 여기서 양쪽을 어떻게 state할까?
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetDir(Vector2f(-1.f, GetDir().y));
		// 지금 점프가 아니면 걷기로
		if (MARIO_STATE::JUMP != m_eCurState)
			m_eCurState = MARIO_STATE::WALK;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetDir(Vector2f(1.f, GetDir().y));
		if (MARIO_STATE::JUMP != m_eCurState)
			m_eCurState = MARIO_STATE::WALK;
	}
	// //개선 후
	// 속도가 없고, 지금 현재 점프상태가 아니거나 땅 위면					
	//if (MARIO_STATE::JUMP != m_eCurState || IsGround())
	if (0.f >= GetRigidbody()->GetSpeed() 
		&& MARIO_STATE::JUMP != m_eCurState || IsGround())
	{
		// 이건 idle 상태다.
		m_eCurState = MARIO_STATE::IDLE;
	}
	float velocity = GetRigidbody()->GetVelocity().y;
	float maxvelocity = GetRigidbody()->GetMaxVelocity().y;
	float posy = velocity * _dt;
	float posmaxy = maxvelocity * _dt;
	if (posy >= posmaxy / 2  && m_eCurState == MARIO_STATE::JUMP)
	{
		m_eCurState = MARIO_STATE::DOWN;
		SetDir(Vector2f(GetDir().x, 1.f));
	}
	//if (m_ePrevState == MARIO_STATE::JUMP && 
	//	GetRigidbody()->GetVelocity().y >= GetRigidbody()->GetMaxVelocity().y)
	//{
	//	SetDir(Vector2f(GetDir().x, 1.f));
	//	m_eCurState = MARIO_STATE::DOWN;
	//}
	// //개선 전
	//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)	
	//	&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//{
	//	m_eCurState = MARIO_STATE::IDLE;
	//}
	//if (m_acctime >=1.f && MARIO_STATE::JUMP == m_eCurState)
	//if (GetPos().y <= GetPos().y +600.f && MARIO_STATE::JUMP == m_eCurState)
	//{
	//	m_acctime = 0.f;
	//	m_eCurState = MARIO_STATE::DOWN;
	//	SetDir(Vector2f(0.f, 1.f));
	//}
}

void Player::AnimationUpdate(float _dt)
{
	// 상태가 달라졌으면 애니메이션 ㄱㄱ   // 이렇게 이전방향 안할거면 walk_left, walk_right 하자.
//	if (m_ePrevState == m_eCurState && m_prevdir == m_dir)
	if (m_ePrevState == m_eCurState && GetPrevDir() == GetDir())
		return;
	switch (m_eCurState)
	{
	case MARIO_STATE::IDLE:
	{
		//if (m_dir.x > 0) // 오른쪽
		if (GetDir().x > 0) // 오른쪽
		{
			GetAnimator()->PlayAnim("marioIdleRight", true);
		}
		//else if (m_dir.x < 0) // 왼쪽
		else if (GetDir().x < 0) // 왼쪽
		{
			GetAnimator()->PlayAnim("marioIdleLeft", true);
		}
	}
	break;
	case MARIO_STATE::WALK:
		//if (m_dir.x > 0)
		if (GetDir().x > 0)
		{
			GetAnimator()->PlayAnim("marioRight", true);
		}
		//else if (m_dir.x < 0)
		else if (GetDir().x < 0)
		{
			GetAnimator()->PlayAnim("marioLeft", true);
		}
		break;
	case MARIO_STATE::JUMP:
		//if (m_dir.x > 0)
		if (GetDir().x > 0)
		{
			GetAnimator()->PlayAnim("marioJumpRight", true);
		}
		//else if (m_dir.x < 0)
		else if (GetDir().x < 0)
		{
			GetAnimator()->PlayAnim("marioJumpLeft", true);
		}
		break;
	case MARIO_STATE::DOWN:
		//if (m_dir.x > 0)
		if (GetDir().x > 0)
		{
			GetAnimator()->PlayAnim("marioJumpRight", true);
		}
		//else if (m_dir.x < 0)
		else if (GetDir().x < 0)
		{
			GetAnimator()->PlayAnim("marioJumpLeft", true);
		}
		break;
	case MARIO_STATE::DIE:
	{
		GetAnimator()->PlayAnim("mariodie", false);
		m_diesound.play();
		m_acctime += _dt;
		if (m_acctime >= 3.f)
		{
			m_acctime = 0.f;
			EventMgr::GetInst()->DeleteObject(this);
		}
	}
		break;
	default:
		break;
	}
}
