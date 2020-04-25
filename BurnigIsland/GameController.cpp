#include <DxLib.h>
#include <math.h>
#include "GameController.h"

GameController::GameController()
{
	_mouseCount_Left = 0;
	for (int i = 0; i < ISLAND_NUM; i++) {
		_island[i] = new Island();
		_island[i]->GetMyNumber(i);
	}
	//_enemy[0] = new Enemy(320, 590);
	//_enemy[0]->_liveFlag = true;
	//_enemy[1] = new Enemy(590, 320);
	//_enemy[2] = new Enemy(320, 50);
	//_enemy[3] = new Enemy(50, 320);
	for (int i = 0; i < ENEMY_NUM; i++) {
		_enemy[i] = new Enemy();
	}

	int direction = 90;

	_island[0]->_posX = 320;
	_island[0]->_posY = 320;

	_island[1]->_posX = 320 + direction;
	_island[1]->_posY = 320 - 30;

	_island[2]->_posX = 320 - 30;
	_island[2]->_posY = 320 - direction;

	_island[3]->_posX = 320 - direction;
	_island[3]->_posY = 320 + 30;

	_island[4]->_posX = 320 + 30;
	_island[4]->_posY = 320 + direction;

	_island[5]->_posX = 320 + direction * 2 - 10;
	_island[5]->_posY = 320 + 10;

	_island[6]->_posX = 320 + 10;
	_island[6]->_posY = 320 - direction * 2 + 10;

	_island[7]->_posX = 320 - direction * 2 + 10;
	_island[7]->_posY = 320 - 10;

	_island[8]->_posX = 320 - 10;
	_island[8]->_posY = 320 + direction * 2 - 10;

	_island[9]->_posX = 320 + direction * 3;
	_island[9]->_posY = 320;

	_island[10]->_posX = 320;
	_island[10]->_posY = 320 - direction * 3;

	_island[11]->_posX = 320 - direction * 3;
	_island[11]->_posY = 320;

	_island[12]->_posX = 320;
	_island[12]->_posY = 320 + direction * 3;

	_island[13]->_posX = 320 + direction - 10;
	_island[13]->_posY = 320 - direction;

	_island[14]->_posX = 320 - direction;
	_island[14]->_posY = 320 - direction + 10;

	_island[15]->_posX = 320 - direction + 10;
	_island[15]->_posY = 320 + direction;

	_island[16]->_posX = 320 + direction;
	_island[16]->_posY = 320 + direction - 10;

	_island[17]->_posX = 320 + direction * 2;
	_island[17]->_posY = 320 - direction;

	_island[18]->_posX = 320 + direction * 2;
	_island[18]->_posY = 320 - direction * 2;

	_island[19]->_posX = 320 + direction;
	_island[19]->_posY = 320 - direction * 2;

	_island[20]->_posX = 320 - direction;
	_island[20]->_posY = 320 - direction * 2;

	_island[21]->_posX = 320 - direction * 2;
	_island[21]->_posY = 320 - direction * 2;

	_island[22]->_posX = 320 - direction * 2;
	_island[22]->_posY = 320 - direction;

	_island[23]->_posX = 320 - direction * 2;
	_island[23]->_posY = 320 + direction;

	_island[24]->_posX = 320 - direction * 2;
	_island[24]->_posY = 320 + direction * 2;

	_island[25]->_posX = 320 - direction;
	_island[25]->_posY = 320 + direction * 2;

	_island[26]->_posX = 320 + direction;
	_island[26]->_posY = 320 + direction * 2;

	_island[27]->_posX = 320 + direction * 2;
	_island[27]->_posY = 320 + direction * 2;

	_island[28]->_posX = 320 + direction * 2;
	_island[28]->_posY = 320 + direction;

	_island[29]->_posX = 320 + direction * 3 - 10;
	_island[29]->_posY = 320 - direction * 3 + 10;

	_island[30]->_posX = 320 - direction * 3 + 10;
	_island[30]->_posY = 320 - direction * 3 + 10;

	_island[31]->_posX = 320 - direction * 3 + 10;
	_island[31]->_posY = 320 + direction * 3 - 10;

	_island[32]->_posX = 320 + direction * 3 - 10;
	_island[32]->_posY = 320 + direction * 3 - 10;

	_fireReloadCount = 0;
	_fireReloadFlag = false;

	_enemyResponCount = 420;
	_enemyResponFlag = false;

	_time.Init();
}

GameController::~GameController()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		delete _island[i];
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		delete _enemy[i];
	}
	//delete _enemy[0];
}

void GameController::Init()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		_island[i]->Init();
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		_enemy[i]->Init();
	}
	_player.Init();
	_rope.Init();
	_time.Init();

	_fireReloadCount = 0;
	_fireReloadFlag = false;

	_enemyResponCount = 420;
	_enemyResponFlag = false;

	int direction = 90;

	_island[0]->_posX = 320;
	_island[0]->_posY = 320;

	_island[1]->_posX = 320 + direction;
	_island[1]->_posY = 320 - 30;

	_island[2]->_posX = 320 - 30;
	_island[2]->_posY = 320 - direction;

	_island[3]->_posX = 320 - direction;
	_island[3]->_posY = 320 + 30;

	_island[4]->_posX = 320 + 30;
	_island[4]->_posY = 320 + direction;

	_island[5]->_posX = 320 + direction * 2 - 10;
	_island[5]->_posY = 320 + 10;

	_island[6]->_posX = 320 + 10;
	_island[6]->_posY = 320 - direction * 2 + 10;

	_island[7]->_posX = 320 - direction * 2 + 10;
	_island[7]->_posY = 320 - 10;

	_island[8]->_posX = 320 - 10;
	_island[8]->_posY = 320 + direction * 2 - 10;

	_island[9]->_posX = 320 + direction * 3;
	_island[9]->_posY = 320;

	_island[10]->_posX = 320;
	_island[10]->_posY = 320 - direction * 3;

	_island[11]->_posX = 320 - direction * 3;
	_island[11]->_posY = 320;

	_island[12]->_posX = 320;
	_island[12]->_posY = 320 + direction * 3;

	_island[13]->_posX = 320 + direction - 10;
	_island[13]->_posY = 320 - direction;

	_island[14]->_posX = 320 - direction;
	_island[14]->_posY = 320 - direction + 10;

	_island[15]->_posX = 320 - direction + 10;
	_island[15]->_posY = 320 + direction;

	_island[16]->_posX = 320 + direction;
	_island[16]->_posY = 320 + direction - 10;

	_island[17]->_posX = 320 + direction * 2;
	_island[17]->_posY = 320 - direction;

	_island[18]->_posX = 320 + direction * 2;
	_island[18]->_posY = 320 - direction * 2;

	_island[19]->_posX = 320 + direction;
	_island[19]->_posY = 320 - direction * 2;

	_island[20]->_posX = 320 - direction;
	_island[20]->_posY = 320 - direction * 2;

	_island[21]->_posX = 320 - direction * 2;
	_island[21]->_posY = 320 - direction * 2;

	_island[22]->_posX = 320 - direction * 2;
	_island[22]->_posY = 320 - direction;

	_island[23]->_posX = 320 - direction * 2;
	_island[23]->_posY = 320 + direction;

	_island[24]->_posX = 320 - direction * 2;
	_island[24]->_posY = 320 + direction * 2;

	_island[25]->_posX = 320 - direction;
	_island[25]->_posY = 320 + direction * 2;

	_island[26]->_posX = 320 + direction;
	_island[26]->_posY = 320 + direction * 2;

	_island[27]->_posX = 320 + direction * 2;
	_island[27]->_posY = 320 + direction * 2;

	_island[28]->_posX = 320 + direction * 2;
	_island[28]->_posY = 320 + direction;

	_island[29]->_posX = 320 + direction * 3 - 10;
	_island[29]->_posY = 320 - direction * 3 + 10;

	_island[30]->_posX = 320 - direction * 3 + 10;
	_island[30]->_posY = 320 - direction * 3 + 10;

	_island[31]->_posX = 320 - direction * 3 + 10;
	_island[31]->_posY = 320 + direction * 3 - 10;

	_island[32]->_posX = 320 + direction * 3 - 10;
	_island[32]->_posY = 320 + direction * 3 - 10;

}

void GameController::Title()
{
}

void GameController::GamePlay()
{
	_time.TimeCourse();

	OnMouseButtonLeft();
	OnMouseButtonRight();

	if (_fireReloadFlag) {
		_fireReloadCount++;
	}
	if (_fireReloadCount > 300) {
		_fireReloadCount = 0;
		_fireReloadFlag = false;
	}

	_enemyResponCount++;
	int levelCheck = 0;
	if (_time.GetGameTime() < 1200) {
		levelCheck = 480;
	}
	else if (_time.GetGameTime() < 2400) {
		levelCheck = 360;
	}
	else {
		levelCheck = 240;
	}

	if (_enemyResponCount > levelCheck) {
		_enemyResponCount = 0;
		_enemyResponFlag = true;
	}
	if (_enemyResponFlag) {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (_enemy[i]->_liveFlag)continue;
			EnemySpawner(_enemy[i]);
			_enemyResponFlag = false;
			break;
		}
	}

	int num_p = 0;
	for (int i = 0; i < ISLAND_NUM; i++) {
		if (_island[i]->PlayerStayCheck(_player.GetPosX(), _player.GetPosY())) {
			num_p = i;
			break;
		}
	}
	int num_e[ENEMY_NUM];
	for (int i = 0; i < ENEMY_NUM; i++) {
		num_e[i] = 0;
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			if (_island[j]->EnemyStayCheck((int)_enemy[i]->_posX, (int)_enemy[i]->_posY)) {
				num_e[i] = j;
				if (_island[j]->_islandState == _island[j]->FIRE) {
					_enemy[i]->Deth();
				}
			}
		}
	}
	for (int i = 0; i < ISLAND_NUM; i++) {
		if (_island[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
			bool connectCheck = false;
			for (int j = 0; j < ISLAND_NUM; j++) {
				if (_rope.GetConnectFlag(i, j)			// 反対側からもロープをかけられる
					|| _rope.GetConnectFlag(num_p, j))	// 自分がいる島と繋がっているか
				{
					connectCheck = true;
				}
			}
			if (!connectCheck) {
				if (_island[num_p]->_posX == 320 && _island[num_p]->_posY == 320) {

				}
				else {
					continue;
				}
			}
			_island[num_p]->CrossCheck(_island[i]);
			if (_mouseCount_Left == 1) { // 左クリックした瞬間
				if (_island[i]->_posX - CIRCLE_ROTATE < _mousePosX_Left && _mousePosX_Left < _island[i]->_posX + CIRCLE_ROTATE &&
					_island[i]->_posY - CIRCLE_ROTATE < _mousePosY_Left && _mousePosY_Left < _island[i]->_posY + CIRCLE_ROTATE &&
					!_rope.GetConnectFlag(num_p, i))
				{
					if (_island[i]->_islandState == _island[i]->BURN) {
						_island[i]->_islandState = _island[i]->GRASS;
						_rope.Minus(50);
					}
					_rope.Connect(num_p, i);
					_rope.Minus(LengthCheck(_island[num_p]->_posX, _island[num_p]->_posY, _island[i]->_posX, _island[i]->_posY));
				}
			}
		}
	}

	if (_mouseCount_Left == 1) { // 左クリックした瞬間
		for (int i = 0; i < ISLAND_NUM; i++) {
			if (_island[i]->_posX - CIRCLE_ROTATE < _mousePosX_Left && _mousePosX_Left < _island[i]->_posX + CIRCLE_ROTATE &&
				_island[i]->_posY - CIRCLE_ROTATE < _mousePosY_Left && _mousePosY_Left < _island[i]->_posY + CIRCLE_ROTATE)
			{
				_player.Move(_island[i]->_posX, _island[i]->_posY);
			}
		}
	}
	if (_mouseCount_Right == 1) { // 右クリックした瞬間
		for (int i = 0; i < ISLAND_NUM; i++) {
			if (_island[i]->_posX - CIRCLE_ROTATE < _mousePosX_Right && _mousePosX_Right < _island[i]->_posX + CIRCLE_ROTATE &&
				_island[i]->_posY - CIRCLE_ROTATE < _mousePosY_Right && _mousePosY_Right < _island[i]->_posY + CIRCLE_ROTATE)
			{
				if (!_fireReloadFlag) {
					_island[i]->Burning();
					_fireReloadFlag = true;
					_rope.AllRecovery();
				}
			}
		}
	}

	for (int i = 0; i < ISLAND_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			if (_rope.GetConnectFlag(i, j)) {
				if (_island[i]->_islandState == _island[i]->FIRE) {
					_rope.Burn(i, j);
					_island[j]->_fireStartFlag = true;
				}
				if (_island[j]->_islandState == _island[j]->FIRE) {
					_rope.Burn(i, j);
					_island[i]->_fireStartFlag = true;
				}
			}
		}
	}

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!_enemy[i]->_liveFlag)continue;
		if (_enemy[i]->_ropemode) {
			for (int j = 0; j < ISLAND_NUM; j++) {
				if (j == _enemy[i]->_lastTouchIsland)continue;
				if ((int)_enemy[i]->_posX <= _island[j]->_posX + 1 && (int)_enemy[i]->_posX >= _island[j]->_posX - 1
					&& (int)_enemy[i]->_posY <= _island[j]->_posY + 1 && (int)_enemy[i]->_posY >= _island[j]->_posY - 1) {
					_enemy[i]->_ropemode = false;
				}
			}
		}
	}

	int v_posX[ENEMY_NUM] = { 1000 ,1000 ,1000 ,1000 }, v_posY[ENEMY_NUM] = { 1000 ,1000 ,1000 ,1000 };
	for (int j = 0; j < ENEMY_NUM; j++) {
		if (!_enemy[j]->_liveFlag)continue;
		int max_degree = 0;
		double max_angle = 0;
		int count = 0;
		for (int i = 0; i < ISLAND_NUM; i++) {
			if (i == num_e[j])continue;
			//if (i == _enemy[j]->_lastTouchIsland)continue;
			if (_island[i]->EnemyDistanseCheck((int)_enemy[j]->_posX, (int)_enemy[j]->_posY)) {
				if (_rope.GetConnectFlag(num_e[j], i) && !_enemy[j]->_ropemode) {
					//if (i == _enemy[j]->_lastTouchIsland) {
					//	bool lastCheck = 0;
					//	for (int k = 0; k < ISLAND_NUM; k++) {
					//		if (k == i)continue;
					//		if (_rope._connectDate[num_e[j]][k] == 1 || _rope._connectDate[k][num_e[j]] == 1) {
					//			lastCheck = 1;
					//			break;
					//		}
					//	}
					//	if (lastCheck == 1)
					//		continue;
					//}

					if (i == _enemy[j]->_lastTouchIsland)continue;

					//_enemy[j]->_ropemode = true;
					//_enemy[j]->_lastTouchIsland = num_e[j];

					//double ei, eix, eiy;

					////eix = _island[i]->_posX - _enemy[j]->_posX;
					////eiy = _island[i]->_posY - _enemy[j]->_posY;

					//eix = _island[i]->_posX - _island[num_e[j]]->_posX;
					//eiy = _island[i]->_posY - _island[num_e[j]]->_posY;

					////ei = (int)sqrt(eix * eix + eiy * eiy);
					//ei = sqrt(eix * eix + eiy * eiy);
					////ei = 90;

					//_enemy[j]->_speedX = (eix / ei) / 2;
					//_enemy[j]->_speedY = (eiy / ei) / 2;

					/////////////////////////////////////////////////////////////

					//double ix, iy, ex, ey;

					//ex = cos(_enemy[j]->_angle);
					//ey = sin(_enemy[j]->_angle);
					//ix = _island[i]->_posX - _island[num_e[j]]->_posX;
					//iy = _island[i]->_posY - _island[num_e[j]]->_posY;

					//_enemy[j]->_angle = (ix * ey - iy * ex < 0.0) ? +M_PI / 180 : -M_PI / 180;

					//_enemy[j]->_speedX = cos(_enemy[j]->_angle);
					//_enemy[j]->_speedY = sin(_enemy[j]->_angle);

					/////////////////////////////////////////////////////////////

					_enemy[j]->_angle = atan2(_island[i]->_posY - _island[num_e[j]]->_posY, _island[i]->_posX - _island[num_e[j]]->_posX);

					//_enemy[j]->_angle = atan2(_island[i]->_posY - _enemy[j]->_posY, _island[i]->_posX - _enemy[j]->_posX);
					double x1, y1, x2, y2, xy1, xy2, n_x1, n_y1, n_x2, n_y2;

					x1 = _island[_enemy[j]->_lastTouchIsland]->_posX - _island[num_e[j]]->_posX;
					y1 = _island[_enemy[j]->_lastTouchIsland]->_posY - _island[num_e[j]]->_posY;
					x2 = _island[i]->_posX - _island[num_e[j]]->_posX;
					y2 = _island[i]->_posY - _island[num_e[j]]->_posY;

					xy1 = sqrt(x1 * x1 + y1 * y1);
					xy2 = sqrt(x2 * x2 + y2 * y2);

					n_x1 = x1 / xy1;
					n_y1 = y1 / xy1;
					n_x2 = x2 / xy2;
					n_y2 = y2 / xy2;

					double dis_angle = atan2(n_x1 * n_y2 - n_x2 * n_y1, n_x1 * n_x2 + n_y1 * n_y2);
					//double dis_angle = atan2(x1 * y2 - x2 * y1, x1 * x2 + y1 * y2);
					//int degree = dis_angle * (180 / M_PI);
					int degree = (dis_angle * (180 / M_PI) < 0.0) ? (dis_angle * (180 / M_PI)) + 360 : dis_angle * (180 / M_PI);

					//double xx, yy;

					//xx = _island[_enemy[j]->_lastTouchIsland]->_posX - _island[i]->_posX;
					//yy = _island[_enemy[j]->_lastTouchIsland]->_posY - _island[i]->_posY;

					//double aa = atan2(yy, xx);
					////int degree = (xx < 0.0) ? aa * (180 / M_PI) + 360 : aa * (180 / M_PI);
					//int degree = aa * (180 / M_PI);

					if (count == 0) {
						max_degree = degree;
						max_angle = _enemy[j]->_angle;
					}
					else {
						if (max_degree < degree) {
							max_angle = _enemy[j]->_angle;
							max_degree = degree;
						}
					}

					//int degree = _enemy[j]->_angle * (180 / M_PI);
					//if (count == 0) {
					//	max_degree = degree;
					//	max_angle = _enemy[j]->_angle;
					//}
					//else {
					//	if (max_degree < degree) {
					//		max_angle = _enemy[j]->_angle;
					//		max_degree = degree;
					//	}
					//}

					//_enemy[j]->_speedX = cos(_enemy[j]->_angle);
					//_enemy[j]->_speedY = sin(_enemy[j]->_angle);

					count++;
				}
				else
				{
					int x = abs(_island[0]->_posX - _island[i]->_posX);
					int y = abs(_island[0]->_posY - _island[i]->_posY);
					int xx = abs(_island[0]->_posX - v_posX[j]);
					int yy = abs(_island[0]->_posY - v_posY[j]);
					if (x * x + y * y < xx * xx + yy * yy) {
						v_posX[j] = _island[i]->_posX;
						v_posY[j] = _island[i]->_posY;
					}
				}
			}
		}
		if (count > 0) {
			_enemy[j]->_ropemode = true;
			_enemy[j]->_angle = max_angle;
			_enemy[j]->_speedX = cos(_enemy[j]->_angle);
			_enemy[j]->_speedY = sin(_enemy[j]->_angle);
			_enemy[j]->_lastTouchIsland = num_e[j];
		}
		else {
			bool lastCheck = 0;
			for (int k = 0; k < ISLAND_NUM; k++) {
				if (k == _enemy[j]->_lastTouchIsland)continue;
				if (_rope.GetConnectFlag(num_e[j], k)) {
					lastCheck = 1;
					break;
				}
			}
			if (lastCheck == 0 && _rope.GetConnectFlag(num_e[j], _enemy[j]->_lastTouchIsland) && !_enemy[j]->_ropemode) {
				_enemy[j]->_angle = atan2(_island[_enemy[j]->_lastTouchIsland]->_posY - _island[num_e[j]]->_posY, _island[_enemy[j]->_lastTouchIsland]->_posX - _island[num_e[j]]->_posX);
				_enemy[j]->_speedX = cos(_enemy[j]->_angle);
				_enemy[j]->_speedY = sin(_enemy[j]->_angle);
				_enemy[j]->_ropemode = true;
				_enemy[j]->_lastTouchIsland = num_e[j];
			}
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (_enemy[i]->_moveFlag) {
			//if ((int)_enemy[i]->_posX <= 320 + 1 && (int)_enemy[i]->_posX >= 320 - 1
			//	&& (int)_enemy[i]->_posY <= 320 + 1 && (int)_enemy[i]->_posY >= 320 - 1) {
			if ((int)_enemy[i]->_posX == 320 && (int)_enemy[i]->_posY == 320) {
				//_enemy[i]->Init();
				_player.Damage();
			}
			else {
				_enemy[i]->_posX = v_posX[i];
				_enemy[i]->_posY = v_posY[i];
				_enemy[i]->_moveFlag = false;
				_enemy[i]->_lastTouchIsland = num_e[i];
				//if ((int)_enemy[i]->_posX <= 320 + 1 && (int)_enemy[i]->_posX >= 320 - 1
				//	&& (int)_enemy[i]->_posY <= 320 + 1 && (int)_enemy[i]->_posY >= 320 - 1) {
				if ((int)_enemy[i]->_posX == 320 && (int)_enemy[i]->_posY == 320) {
					_player.Damage();
				}
			}
		}
		else {
			//if ((int)_enemy[i]->_posX <= 320 + 1 && (int)_enemy[i]->_posX >= 320 - 1
			//	&& (int)_enemy[i]->_posY <= 320 + 1 && (int)_enemy[i]->_posY >= 320 - 1) {
			if ((int)_enemy[i]->_posX == 320 && (int)_enemy[i]->_posY == 320) {
				//_enemy[i]->Init();
				_player.Damage();
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_R)) {
		Init();
	}
	if (!_player.GetLive()) {
		DrawFormatString(100, 10, GetColor(255, 255, 255), "GAMEOVER");
	}
}

void GameController::Result()
{
}

void GameController::Draw()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			if (_rope.GetConnectFlag(i, j)) {
				if (_rope.GetFireFlag(i, j)) {
					DrawLine(_island[i]->_posX, _island[i]->_posY, _island[j]->_posX, _island[j]->_posY, GetColor(255, 0, 0), 3);
				}
				else {
					DrawLine(_island[i]->_posX, _island[i]->_posY, _island[j]->_posX, _island[j]->_posY, GetColor(255, 255, 255), 3);
				}
			}
			DrawFormatString(_island[i]->_posX, _island[i]->_posY, GetColor(0, 0, 0), "%d", i);
		}
	}
	DrawFormatString(10, 10, GetColor(255, 255, 255), "hp : %d", _player.GetHP());
	if (!_fireReloadFlag) {
		DrawFormatString(10, 30, GetColor(255, 255, 255), "撃てる");
	}
	DrawLine(100, 20, 100 + (_rope.GetRopeLife() / 2), 20, GetColor(100, 200, 100), 10);
}

void GameController::All()
{
	GamePlay();
	for (int i = 0; i < ISLAND_NUM; i++) {
		_island[i]->All();
	}
	Draw();
	for (int i = 0; i < ENEMY_NUM; i++) {
		_enemy[i]->All();
	}
	_player.All();
	_rope.All();
}

int GameController::OnMouseButtonLeft()
{
	_mouse_Left = GetMouseInput();
	if (_mouse_Left & MOUSE_INPUT_LEFT) {
		GetMousePoint(&_mousePosX_Left, &_mousePosY_Left);
		_mouseCount_Left++;
		return _mouseCount_Left;
	}
	if (_mouseCount_Left > 0) {
		_mouseCount_Left = -1;
		return _mouseCount_Left;
	}
	else if (_mouseCount_Left < 0) {
		_mouseCount_Left = 0;
		return _mouseCount_Left;
	}
	else {
		return _mouseCount_Left;
	}
}

int GameController::OnMouseButtonRight()
{
	_mouse_Right = GetMouseInput();
	if (_mouse_Right & MOUSE_INPUT_RIGHT) {
		GetMousePoint(&_mousePosX_Right, &_mousePosY_Right);
		_mouseCount_Right++;
		return _mouseCount_Right;
	}
	if (_mouseCount_Right > 0) {
		_mouseCount_Right = -1;
		return _mouseCount_Right;
	}
	else if (_mouseCount_Right < 0) {
		_mouseCount_Right = 0;
		return _mouseCount_Right;
	}
	else {
		return _mouseCount_Right;
	}
}

int GameController::LengthCheck(int posX1, int posY1, int posX2, int posY2)
{
	auto x = abs(posX1 - posX2);
	auto y = abs(posY1 - posY2);

	auto ans = (int)sqrt(x * x + y * y);
	return ans;
}

void GameController::EnemySpawner(Enemy* enemy)
{
	//SRand(2);//左上
	//SRand(7);//下
	//SRand(15);// 左
	//SRand(12);// 右
	int random = GetRand(8 - 1);
	switch (random) {
	case 0:
		enemy->Instantiate(320, 590);
		break;
	case 1:
		enemy->Instantiate(60, 580);
		break;
	case 2:
		enemy->Instantiate(50, 320);
		break;
	case 3:
		enemy->Instantiate(60, 60);
		break;
	case 4:
		enemy->Instantiate(320, 50);
		break;
	case 5:
		enemy->Instantiate(580, 60);
		break;
	case 6:
		enemy->Instantiate(590, 320);
		break;
	case 7:
		enemy->Instantiate(580, 580);
		break;
	}
}