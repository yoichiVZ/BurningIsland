#include <DxLib.h>
#include "Player.h"

Player::Player()
{
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	_posX = 320;
	_posY = 320;
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