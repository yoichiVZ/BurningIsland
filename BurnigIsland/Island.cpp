#include <DxLib.h>
#include "Island.h"
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
	_rotation = CIRCLE_ROTATE;
	_distanseFlag = false;
	_mouseCount_Right = 0;
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

	DrawBox(_posX - CIRCLE_ROTATE, _posY - CIRCLE_ROTATE, _posX + CIRCLE_ROTATE, _posY + CIRCLE_ROTATE, GetColor(255, 255, 255), FALSE);
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

	if (x * x + y * y <= ((PLAYER_ROTATE * ROPE_DISTANSE) + CIRCLE_ROTATE) * ((PLAYER_ROTATE * ROPE_DISTANSE) + CIRCLE_ROTATE)) {
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

	if (x * x + y * y <= (PLAYER_ROTATE + CIRCLE_ROTATE) * (PLAYER_ROTATE + CIRCLE_ROTATE)) {
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

	if (x * x + y * y <= ((PLAYER_ROTATE * ROPE_DISTANSE) + CIRCLE_ROTATE) * ((PLAYER_ROTATE * ROPE_DISTANSE) + CIRCLE_ROTATE)) {
		return true;
	}

	return false;
}

bool Island::EnemyStayCheck(int ex, int ey)
{
	auto x = abs(ex - _posX);
	auto y = abs(ey - _posY);

	if (x * x + y * y <= (PLAYER_ROTATE + CIRCLE_ROTATE) * (PLAYER_ROTATE + CIRCLE_ROTATE)) {
		return true;
	}

	return false;
}

void Island::CrossCheck(Island* island)
{
	DrawLine(_posX, _posY, island->_posX, island->_posY, GetColor(150, 150, 150), 3);

}

void Island::GetOnMouseRight(int mouseCount)
{
	_mouseCount_Right = mouseCount;
}

void Island::GetMyNumber(int num)
{
	_myNumber = num;
}

void Island::Burning()
{
	if (_posX == 320 && _posY == 320) return;
	if (_islandState == GRASS) {
		_islandState = FIRE;
	}
}