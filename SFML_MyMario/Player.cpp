#include "pch.h"
#include "Player.h"
#include "Collider.h"
#include "ResMgr.h"
#include "WindowMgr.h"
#include "Rigidbody.h"
#include "Camera.h"
Player::Player()
	: circleTime(1.f)
	, curTime(0.f)
	, m_circle(NULL)
{
	GetSprite().setTexture(ResMgr::GetInst()->GetTexture("idle"));
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2
						,GetSprite().getGlobalBounds().height / 2);

	CreateRigidbody();
}
void Player::Update(float _dt)
{
	Camera::GetInst()->SetPos(GetPos());
	MoveUpdate(_dt);
	MakeCircleShape();
	if (curTime < circleTime) curTime += _dt;
}

void Player::Render()
{
	GET_WINDOW.draw(GetSprite());
}

void Player::EnterCollision(Collider* _pOther)
{
}

void Player::ExitCollision(Collider* _pOther)
{
}

void Player::StayCollision(Collider* _pOther)
{
}

void Player::MakeCircleShape()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Vector2i pos = sf::Mouse::getPosition();
		m_circle = CircleShape(0.1f);
	}
}

void Player::MoveUpdate(float _dt)
{
	Rigidbody* pRigidbody = GetRigidbody();
	float movespeed = 100.f;
	Vector2f vPos = GetPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		movespeed *= 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		pRigidbody->AddForce(Vector2f(-10.f, 0.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		pRigidbody->AddForce(Vector2f(10.f, 0.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		pRigidbody->AddVelocity(Vector2f(30.f, 0.f));

		
	GetSprite().setPosition(vPos);
}
