#include <DxLib.h>
#include <math.h>
#include "Bullet.h"
#include "WindowInfo.h"

Bullet::Bullet()
{
	Init();
}

void Bullet::Init()
{
	_posX = 0,_posY = 0;
	_movementX = 0, _movementY = 0;
	_liveFlag = false;
}

void Bullet::Update()
{
	if (!_liveFlag)return;
	Move();
	if (0 > _posX + BULLET_ROTATE || WindowInfo::Screen_Width < _posX - BULLET_ROTATE
		|| 0 > _posY + BULLET_ROTATE || WindowInfo::Screen_Height < _posY - BULLET_ROTATE) {
		Deth();
	}
}

void Bullet::Draw()
{
	if (!_liveFlag)return;
	DrawCircle(_posX, _posY, BULLET_ROTATE, GetColor(255, 0, 0), TRUE);
}

void Bullet::All()
{
	Update();
	Draw();
}

void Bullet::SetTarget(int posX, int posY, int target_posX, int target_posY)
{
	_liveFlag = true;
	
	_posX = posX;
	_posY = posY;

	auto x = target_posX - posX;
	auto y = target_posY - posY;

	auto xy = sqrt(x * x + y * y);

	_movementX = (x / xy) * BULLET_SPEED;
	_movementY = (y / xy) * BULLET_SPEED;
}

void Bullet::Deth()
{
	Init();
}

bool Bullet::GetLiveFlag()
{
	return _liveFlag;
}

void Bullet::Move()
{
	_posX += _movementX;
	_posY += _movementY;
}
