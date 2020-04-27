#include <DxLib.h>
#include "Island.h"

#include "IslandInfo.h"

#include "Player.h"


Island::Island()
{
	Init();
}

Island::~Island()
{
}

void Island::Init()
{
	_posX = 0; _posY = 0;
	_rotation = ISLAND_ROTATE;
	_distanseFlag = false;
	_islandState = GRASS;
	_fireCount = 0;
	_burnCount = 0;
	_fireStartFlag = false;
	_fireStartCount = 0;
}

void Island::Update()
{
	if (_islandState == FIRE) {
		_fireCount++;
		if (_fireCount > 120) {
			_islandState = BURN;
			_fireCount = 0;
		}
	}
	else if (_islandState == BURN) {
		_burnCount++;
		if (_burnCount > 600) {
			_islandState = GRASS;
			_burnCount = 0;
		}
	}
	if (_fireStartFlag) {
		_fireStartCount++;
	}
	if (_fireStartCount > 30) {
		_fireStartCount = 0;
		_fireStartFlag = false;
		Burning();
	}
}

void Island::Draw()
{
	if (_islandState == GRASS)DrawCircle(_posX, _posY, _rotation, GetColor(255, 255, 255), TRUE);
	if (_islandState == FIRE)DrawCircle(_posX, _posY, _rotation, GetColor(200, 0, 0), TRUE);
	if (_islandState == BURN)DrawCircle(_posX, _posY, _rotation, GetColor(100, 100, 100), TRUE);

	if (_distanseFlag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
		if (_playerStayFlag)
			DrawCircle(_posX, _posY, _rotation, GetColor(0, 255, 0), TRUE);
		else
			DrawCircle(_posX, _posY, _rotation, GetColor(0, 155, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	else {
		//DrawCircle(_posX, _posY, _rotation, GetColor(255, 255, 255), TRUE);
	}

	DrawBox(_posX - ISLAND_ROTATE, _posY - ISLAND_ROTATE, _posX + ISLAND_ROTATE, _posY + ISLAND_ROTATE, GetColor(255, 255, 255), FALSE);
}

void Island::All()
{
	Update();
	Draw();
}

bool Island::DistanseCheck(int px, int py)
{
	auto x = abs(px - _posX);
	auto y = abs(py - _posY);

	if (x * x + y * y <= ((PLAYER_ROTATE * ROPE_DISTANSE) + ISLAND_ROTATE) * ((PLAYER_ROTATE * ROPE_DISTANSE) + ISLAND_ROTATE)) {
		_distanseFlag = true;
		return true;
	}

	_distanseFlag = false;
	return false;
}

bool Island::PlayerStayCheck(int px, int py)
{
	auto x = abs(px - _posX);
	auto y = abs(py - _posY);

	if (x * x + y * y <= (PLAYER_ROTATE + ISLAND_ROTATE) * (PLAYER_ROTATE + ISLAND_ROTATE)) {
		_playerStayFlag = true;
		return true;
	}

	_playerStayFlag = false;
	return false;
}

bool Island::EnemyDistanseCheck(int ex, int ey)
{
	auto x = abs(ex - _posX);
	auto y = abs(ey - _posY);

	if (x * x + y * y <= ((PLAYER_ROTATE * ROPE_DISTANSE) + ISLAND_ROTATE) * ((PLAYER_ROTATE * ROPE_DISTANSE) + ISLAND_ROTATE)) {
		return true;
	}

	return false;
}

bool Island::EnemyStayCheck(int ex, int ey)
{
	auto x = abs(ex - _posX);
	auto y = abs(ey - _posY);

	if (x * x + y * y <= (PLAYER_ROTATE + ISLAND_ROTATE) * (PLAYER_ROTATE + ISLAND_ROTATE)) {
		return true;
	}

	return false;
}

void Island::CrossCheck(Island* island)
{
	DrawLine(_posX, _posY, island->_posX, island->_posY, GetColor(150, 150, 150), 3);

}

void Island::GetMyNumber(int num)
{
	_myNumber = num;
}

void Island::Burning()
{
	if (_posX == IslandInfo::Base_Island_PosX && _posY == IslandInfo::Base_Island_PosY) return;
	if (_islandState == GRASS) {
		_islandState = FIRE;
	}
}

void Island::Ignition()
{
	_fireStartFlag = true;
}

void Island::SetPosition(int posX, int posY)
{
	_posX = posX;
	_posY = posY;
}

void Island::Revival()
{
	_islandState = GRASS;
}

bool Island::StateCheck_GRASS()
{
	if (_islandState == GRASS)return true;
	return false;
}

bool Island::StateCheck_FIRE()
{
	if (_islandState == FIRE)return true;
	return false;
}

bool Island::StateCheck_BURN()
{
	if (_islandState == BURN)return true;
	return false;
}

int Island::GetPosX()
{
	return _posX;
}

int Island::GetPosY()
{
	return _posY;
}
