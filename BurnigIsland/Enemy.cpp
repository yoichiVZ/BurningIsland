#include "DxLib.h"
#include "Enemy.h"
#include "Island.h"

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(int posX, int posY)
{
	_firstPosX = posX;
	_firstPosY = posY;
	Init();
	_liveFlag = false;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	_jumpMoveCount = 0;
	_posX = 0, _posY = 0;
	_jumpMoveFlag = false;
	_liveFlag = false;
	_ropeModeFlag = false;
	_speedX = 0, _speedY = 0;
	_ropeMoveCount = 0;
	_angle = 0;
	_vertualPosX = 0, _vertualPosY = 0;
	_deletePosX = 0, _deletePosY = 0;
	_lastTouchIslandNumber = 0;
}

void Enemy::Update()
{
	if (!_liveFlag)return;
	if (!_ropeModeFlag)_jumpMoveCount++;
	if (_jumpMoveCount >= 180) {
		_jumpMoveFlag = true;
		_jumpMoveCount = 0;
	}
	RopeMove();
	if ((int)_posX <= 320 + 1 && (int)_posX >= 320 - 1
		&& (int)_posY <= 320 + 1 && (int)_posY >= 320 - 1) {
		Deth();
	}
	//if (((int)_posX == 320  || (int)_posX == 320 - 1)
	//	&& ((int)_posY == 320 || (int)_posY == 320 - 1)) {
	//	Deth();
	//}
}

void Enemy::Draw()
{
	if (!_liveFlag)return;
	DrawCircle((int)_posX, (int)_posY, ENEMY_ROTATE, GetColor(255, 0, 0), TRUE);
}

void Enemy::All()
{
	Update();
	Draw();
}

void Enemy::Deth()
{
	Init();
}

void Enemy::Instantiate(int px, int py)
{
	_posX = px;
	_posY = py;
	_liveFlag = true;
}

void Enemy::JumpMove(int posX, int posY)
{
	_posX = posX;
	_posY = posY;
}

void Enemy::SetSpeed(double speedX, double speedY)
{
	_speedX = speedX;
	_speedY = speedY;
}

void Enemy::SetAngle(double angle)
{
	_angle = angle;
}

void Enemy::SetLastTouchIslandNumber(int lastTouchIslandNumber)
{
	if (lastTouchIslandNumber < 0 || lastTouchIslandNumber >= ISLAND_NUM)return;
	_lastTouchIslandNumber = lastTouchIslandNumber;
}

void Enemy::OffJumpMoveFlag()
{
	_jumpMoveFlag = false;
}

void Enemy::OnRopeModeFlag()
{
	_ropeModeFlag = true;
}

void Enemy::OffRopeModeFlag()
{
	_ropeModeFlag = false;
}

int Enemy::GetPosX()
{
	return _posX;
}

int Enemy::GetPosY()
{
	return _posY;
}

int Enemy::GetLastTouchIslandNumber()
{
	return _lastTouchIslandNumber;
}

double Enemy::GetAngle()
{
	return _angle;
}

bool Enemy::GetRopeModeFlag()
{
	return _ropeModeFlag;
}

bool Enemy::GetLiveFlag()
{
	return _liveFlag;
}

bool Enemy::GetJumpMoveFlag()
{
	return _jumpMoveFlag;
}

void Enemy::RopeMove()
{
	if (!_ropeModeFlag)return;
	_ropeMoveCount++;
	if (_ropeMoveCount > 0) {
		_vertualPosX += _speedX + _deletePosX;
		_vertualPosY += _speedY + _deletePosY;

		_deletePosX = 0;
		_deletePosY = 0;

		if (_vertualPosX >= 1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosX - i < 1) {
					_deletePosX = _vertualPosX - i;
					_vertualPosX = 0;
					break;
				}
			}
			_posX += i;
		}
		else if (_vertualPosX <= -1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosX + i > -1) {
					_deletePosX = _vertualPosX + i;
					_vertualPosX = 0;
					break;
				}
			}
			_posX -= i;
		}
		if (_vertualPosY >= 1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosY - i < 1) {
					_deletePosY = _vertualPosY - i;
					_vertualPosY = 0;
					break;
				}
			}
			_posY += i;
		}
		else if (_vertualPosY <= -1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosY + i > -1) {
					_deletePosY = _vertualPosY + i;
					_vertualPosY = 0;
					break;
				}
			}
			_posY -= i;
		}
	}
}
