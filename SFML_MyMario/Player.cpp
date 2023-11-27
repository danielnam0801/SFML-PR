#include "pch.h"
#include "Player.h"
#include "WindowMgr.h"
#include "Collider.h"
#include "ResMgr.h"
#include "Camera.h"

Player::Player()
{
	GetSprite().setTexture(ResMgr::GetInst()->GetTexture("idle"));
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2,
		GetSprite().getGlobalBounds().height / 2);
}

void Player::Update(float _dt)
{
	Camera::GetInst()->SetPos(Getpos());
	float movespeed = 100.f;
	Vector2f vPos = GetPos();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		movespeed *= 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		vPos.x -= movespeed * _dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		vPos.x += movespeed * _dt;
	GetSprite().setPosition(vPos);
}

void Player::Render()
{
	GET_WINDOW.draw(GetSprite());
}

void Player::EnterCollision(Collider* _other)
{

}

void Player::ExitCollision(Collider* _other)
{

}

void Player::StayCollision(Collider* _other)
{

}
