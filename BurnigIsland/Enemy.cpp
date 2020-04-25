#include "DxLib.h"
#include "Enemy.h"

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
	_moveCount = 0;
	_posX = 0, _posY = 0;
	_moveFlag = false;
	_liveFlag = false;
	_ropemode = false;
	_speedX = 0, _speedY = 0;
	_ropeMoveCount = 0;
	_angle = 0;
	_vertualPosX = 0, _vertualPosY = 0;
	_deletePosX = 0, _deletePosY = 0;
	_lastTouchIsland = 0;
}

void Enemy::Update()
{
	if (!_liveFlag)return;
	if (!_ropemode)_moveCount++;
	if (_moveCount >= 180) {
		_moveFlag = true;
		_moveCount = 0;
	}
	Move();
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

void Enemy::Move()
{
	if (!_ropemode)return;
	_ropeMoveCount++;
	//if (_ropeMoveCount % 2 == 1) {
	if (_ropeMoveCount > 0) {
		//int num_x, vNum_x, num_y, vNum_y;
		//double mCheck;

		//num_x = _speedX;
		//vNum_x = _speedX - 0.5;
		//mCheck = _speedX - 0.5;
		//if (num_x == vNum_x && mCheck >= 0) {
		//	num_x++;
		//}


		//num_y = _speedY;
		//vNum_y = _speedY - 0.5;
		//mCheck = _speedY - 0.5;
		//if (num_y == vNum_y && mCheck >= 0) {
		//	num_y++;
		//}

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

		//_posX += _speedX;
		//_posY += _speedY;

		//int num_x, vNum_x, num_y, vNum_y;

		//num_x = _posX;
		//vNum_x = _posX - 0.5;
		//if (num_x == vNum_x) {
		//	_posX++;
		//}


		//num_y = _posY;
		//vNum_y = _posY - 0.5;
		//if (num_y == vNum_y) {
		//	_posY++;
		//}

		//_ropeMoveCount = 0;
	}
	//_posX += _speedX;
	//_posY += _speedY;
}
