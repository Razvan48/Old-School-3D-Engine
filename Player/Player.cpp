#include "Player.h"

Player::Player(double x, double y, double viewAngle)
{
	this->x = x;
	this->y = y;

	this->viewAngle = viewAngle;
}

Player::~Player()
{

}

void Player::Translate(double x, double y)
{
	this->x += x;
	this->y += y;
}

void Player::Rotate(double angle)
{
	this->viewAngle += angle;

	while (viewAngle >= 2.0 * PI)
	{
		viewAngle -= 2.0 * PI;
	}
	while (viewAngle < 0.0)
	{
		viewAngle += 2.0 * PI;
	}
}

double Player::GetX()
{
	return this->x;
}

double Player::GetY()
{
	return this->y;
}

void Player::SetX(double x)
{
	this->x = x;
}

void Player::SetY(double y)
{
	this->y = y;
}

double Player::GetBodyRadius()
{
	return this->bodyRadius;
}

void Player::SetBodyRadius(double bodyRadius)
{
	this->bodyRadius = bodyRadius;
}

double Player::GetViewAngle()
{
	return this->viewAngle;
}

double Player::GetTransSpeed()
{
	return this->transSpeed;
}

double Player::GetRotSpeed()
{
	return this->rotSpeed;
}

double Player::GetCursorX()
{
	return this->cursorX;
}

void Player::SetCursorX(double cursorX)
{
	this->cursorX = cursorX;
}

void Player::SetFieldOfView(double fov)
{
	this->fov = fov;
}

double Player::GetFieldOfView()
{
	return this->fov;
}

double Player::GetVerticalAngle()
{
	return this->verticalAngle;
}

double Player::GetRunningTransSpeed()
{
	return this->runningTransSpeed;
}

double Player::GetZ()
{
	return this->z;
}

void Player::SetZ(double z)
{
	this->z = z;
}