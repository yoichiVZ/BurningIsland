#include <DxLib.h>
#include <math.h>

#include "Bullet.h"

#include "MyDrawTurn.h"

#include "WindowInfo.h"
#include "IslandInfo.h"
#include "BulletInfo.h"

Bullet::Bullet()
{
	_gh_demonBullet = LoadGraph("Resource\\Image\\AkumaBullet.png");
	GetGraphSize(_gh_demonBullet, &_demonBullet_width, &_demonBullet_height);
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
	if (0 > _posX + BulletInfo::Bullet_Rotation || WindowInfo::Screen_Width < _posX - BulletInfo::Bullet_Rotation
		|| 0 > _posY + BulletInfo::Bullet_Rotation || WindowInfo::Screen_Height < _posY - BulletInfo::Bullet_Rotation) {
		Deth();
	}
}

void Bullet::Draw()
{
	if (!_liveFlag)return;
	MyDrawTurn::Instance().SetDrawItem(_posX - _demonBullet_width / 2, _posY - _demonBullet_height / 2, _gh_demonBullet, 0.5f);
	//DrawCircle(_posX, _posY, BulletInfo::Bullet_Rotation, GetColor(255, 0, 0), TRUE);
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

	_movementX = (x / xy) * BulletInfo::Bullet_Speed;
	_movementY = (y / xy) * BulletInfo::Bullet_Speed;
}

void Bullet::Deth()
{
	Init();
}

bool Bullet::BaseHitCheck()
{
	auto x = abs(IslandInfo::Base_Island_PosX - (int)_posX);
	auto y = abs(IslandInfo::Base_Island_PosY - (int)_posY);

	if (x * x + y * y <= (IslandInfo::Island_Rotation + BulletInfo::Bullet_Rotation) * (IslandInfo::Island_Rotation + BulletInfo::Bullet_Rotation)) {
		return true;
	}

	return false;
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
