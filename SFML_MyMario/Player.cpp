#include "pch.h"
#include "Player.h"
#include "Collider.h"
#include "ResMgr.h"
#include "WindowMgr.h"
#include "Camera.h"
#include "Rigidbody.h"
Player::Player()
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

void Player::MoveUpdate(float _dt)
{
	Rigidbody* pRigidbody = GetRigidbody();
	float movespeed = 100.f;
	Vector2f vPos = GetPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		movespeed *= 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//vPos.x -= movespeed * _dt;
		pRigidbody->AddForce(Vector2f(-10.f,0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//vPos.x += movespeed * _dt;
		pRigidbody->AddForce(Vector2f(10.f,0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		pRigidbody->SetVelocity(Vector2f(30.f, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		pRigidbody->AddVelocity(Vector2f(10.f, 0.f));
	}

	GetSprite().setPosition(vPos);
}

void Player::CircleUpdate(float _dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Vector2i circlePos = WindowMgr::GetInst()->GetWindow().mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition());
		//_circleShape.setPosition(circlePos);
	}
}
