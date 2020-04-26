#include <DxLib.h>
#include "Player.h"

#include "IslandInfo.h"

Player::Player()
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	_posX = IslandInfo::Base_Island_PosX;
	_posY = IslandInfo::Base_Island_PosY;
	_rotation = PLAYER_ROTATE;
	_hp = 3;
}

void Player::Update()
{
}

void Player::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	DrawCircle(_posX, _posY, _rotation * ROPE_DISTANSE, GetColor(0, 255, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawCircle(_posX, _posY, _rotation, GetColor(0, 0, 255), TRUE);
}

void Player::All()
{
	Draw();
}

void Player::Damage()
{
	_hp--;
}

void Player::Move(int posX, int posY)
{
	_posX = posX;
	_posY = posY;
}

int Player::GetPosX()
{
	return _posX;
}

int Player::GetPosY()
{
	return _posY;
}

int Player::GetHP()
{
	return _hp;
}

bool Player::GetLive()
{
	if (_hp <= 0)return false;
	return true;
}
