#include <DxLib.h>
#include "Player.h"

#include "IslandInfo.h"
#include "PlayerInfo.h"

Player::Player()
{
	_sh_damage = LoadSoundMem("Resource\\Sound\\damage.mp3");
	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	_posX = IslandInfo::Base_Island_PosX;
	_posY = IslandInfo::Base_Island_PosY;
	_hp = PlayerInfo::Player_HP;
}

void Player::Update()
{
}

void Player::Draw()
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	//DrawCircle(_posX, _posY, PlayerInfo::Player_Rope_Distance, GetColor(0, 255, 0), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Player::All()
{
	Draw();
}

void Player::Damage()
{
	_hp--;
	PlaySoundMem(_sh_damage, DX_PLAYTYPE_BACK);
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
