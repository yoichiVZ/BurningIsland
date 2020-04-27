#include <DxLib.h>
#include <math.h>
#include "GameController.h"
#include "IslandInfo.h"

GameController::GameController()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		_island[i] = new Island();
		_island[i]->GetMyNumber(i);
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		_enemy[i] = new Enemy();
	}
	Init();
}

GameController::~GameController()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		delete _island[i];
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		delete _enemy[i];
	}
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

	_enemyResponCount = 660;
	_enemyResponFlag = false;

	_mouseCount_Left = 0;
	_mouseCount_Right = 0;

	int direction = 100;

	_island[0]-> SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY);

	_island[1]-> SetPosition(IslandInfo::Base_Island_PosX - direction - 9, IslandInfo::Base_Island_PosY - (direction) + 51);
	_island[2]-> SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 11, IslandInfo::Base_Island_PosY - (direction) + 15);
	_island[3]-> SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction) - 7);
	_island[4]-> SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 11, IslandInfo::Base_Island_PosY - (direction) + 15);
	_island[5]-> SetPosition(IslandInfo::Base_Island_PosX + direction + 9, IslandInfo::Base_Island_PosY - (direction) + 51);

	_island[6]-> SetPosition(IslandInfo::Base_Island_PosX - direction - 60, IslandInfo::Base_Island_PosY - (direction * 2) + 100);
	_island[7]-> SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 65, IslandInfo::Base_Island_PosY - (direction * 2) + 50);
	_island[8]-> SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 15, IslandInfo::Base_Island_PosY - (direction * 2) + 10);
	_island[9]-> SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 2) - 5);
	_island[10]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 15, IslandInfo::Base_Island_PosY - (direction * 2) + 10);
	_island[11]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 65, IslandInfo::Base_Island_PosY - (direction * 2) + 50);
	_island[12]->SetPosition(IslandInfo::Base_Island_PosX + direction + 60, IslandInfo::Base_Island_PosY - (direction * 2) + 100);

	_island[13]->SetPosition(IslandInfo::Base_Island_PosX - direction - 110, IslandInfo::Base_Island_PosY - (direction * 3) + 150);
	_island[14]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 115, IslandInfo::Base_Island_PosY - (direction * 3) + 100);
	_island[15]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 70, IslandInfo::Base_Island_PosY - (direction * 3) + 45);
	_island[16]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 15, IslandInfo::Base_Island_PosY - (direction * 3) + 15);
	_island[17]->SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 3) - 10);
	_island[18]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 15, IslandInfo::Base_Island_PosY - (direction * 3) + 15);
	_island[19]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 70, IslandInfo::Base_Island_PosY - (direction * 3) + 45);
	_island[20]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 115, IslandInfo::Base_Island_PosY - (direction * 3) + 100);
	_island[21]->SetPosition(IslandInfo::Base_Island_PosX + direction + 110, IslandInfo::Base_Island_PosY - (direction * 3) + 150);

	_island[22]->SetPosition(IslandInfo::Base_Island_PosX - direction - 140, IslandInfo::Base_Island_PosY - (direction * 4) + 205);
	_island[23]->SetPosition(IslandInfo::Base_Island_PosX - direction - 110, IslandInfo::Base_Island_PosY - (direction * 4) + 145);
	_island[24]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 115, IslandInfo::Base_Island_PosY - (direction * 4) + 100);
	_island[25]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 70, IslandInfo::Base_Island_PosY - (direction * 4) + 50);
	_island[26]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 15, IslandInfo::Base_Island_PosY - (direction * 4) + 20);
	_island[27]->SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 4) - 5);
	_island[28]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 15, IslandInfo::Base_Island_PosY - (direction * 4) + 20);
	_island[29]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 70, IslandInfo::Base_Island_PosY - (direction * 4) + 50);
	_island[30]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 115, IslandInfo::Base_Island_PosY - (direction * 4) + 100);
	_island[31]->SetPosition(IslandInfo::Base_Island_PosX + direction + 110, IslandInfo::Base_Island_PosY - (direction * 4) + 145);
	_island[32]->SetPosition(IslandInfo::Base_Island_PosX + direction + 140, IslandInfo::Base_Island_PosY - (direction * 4) + 205);

	_island[33]->SetPosition(IslandInfo::Base_Island_PosX - direction - 200, IslandInfo::Base_Island_PosY - (direction * 5) + 200);
	_island[34]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 163, IslandInfo::Base_Island_PosY - (direction * 5) + 88);
	_island[35]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 65, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
	_island[36]->SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 5) - 20);
	_island[37]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 65, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
	_island[38]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 163, IslandInfo::Base_Island_PosY - (direction * 5) + 88);
	_island[39]->SetPosition(IslandInfo::Base_Island_PosX + direction + 200, IslandInfo::Base_Island_PosY - (direction * 5) + 200);

	//_island[40]->SetPosition(IslandInfo::Base_Island_PosX + direction + 200, IslandInfo::Base_Island_PosY - (direction * 5) + 200);
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
	int levelCheck = 360;
	//if (_time.GetGameTime() < 1200) {
	//	levelCheck = 480;
	//}
	//else if (_time.GetGameTime() < 2400) {
	//	levelCheck = 360;
	//}
	//else {
	//	levelCheck = 240;
	//}

	if (_enemyResponCount > levelCheck) {
		_enemyResponCount = 0;
		_enemyResponFlag = true;
	}
	if (_enemyResponFlag) {
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < ENEMY_NUM; i++) {
				if (_enemy[i]->GetLiveFlag())continue;
				EnemySpawn(_enemy[i]);
				_enemyResponFlag = false;
				break;
			}
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
			if (_island[j]->EnemyStayCheck(_enemy[i]->GetPosX(), _enemy[i]->GetPosY())) {
				num_e[i] = j;
				if (_island[j]->StateCheck_FIRE()) {
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
				if (_island[num_p]->_posX == IslandInfo::Base_Island_PosX && _island[num_p]->_posY == IslandInfo::Base_Island_PosY) {

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
					if (_island[i]->StateCheck_BURN()) {
						_island[i]->Revival();
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
				if (_island[i]->StateCheck_FIRE()) {
					_rope.Burn(i, j);
					_island[j]->Ignition();
				}
				if (_island[j]->StateCheck_FIRE()) {
					_rope.Burn(i, j);
					_island[i]->Ignition();
				}
			}
		}
	}

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!_enemy[i]->GetLiveFlag())continue;
		if (_enemy[i]->GetRopeModeFlag()) {
			for (int j = 0; j < ISLAND_NUM; j++) {
				if (j == _enemy[i]->GetLastTouchIslandNumber())continue;
				if (_enemy[i]->GetPosX() <= _island[j]->_posX + 1 && _enemy[i]->GetPosX() >= _island[j]->_posX - 1
					&& _enemy[i]->GetPosY() <= _island[j]->_posY + 1 && _enemy[i]->GetPosY() >= _island[j]->_posY - 1) {
					_enemy[i]->OffRopeModeFlag();
				}
			}
		}
	}

	int v_posX[ENEMY_NUM], v_posY[ENEMY_NUM];
	for (int i = 0; i < ENEMY_NUM; i++) {
		v_posX[i] = _enemy[i]->GetPosX();
		v_posY[i] = _enemy[i]->GetPosY() - 1;
	}
	for (int j = 0; j < ENEMY_NUM; j++) {
		if (!_enemy[j]->GetLiveFlag())continue;

		int max_degree = 0;
		double max_angle = 0;
		int count = 0;

		for (int i = 0; i < ISLAND_NUM; i++) {
			if (i == num_e[j])continue;

			if (_island[i]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
				if (_rope.GetConnectFlag(num_e[j], i) && !_enemy[j]->GetRopeModeFlag()) {
					if (i == _enemy[j]->GetLastTouchIslandNumber())continue;
					if (_enemy[j]->dis_number == 1)continue;

					_enemy[j]->SetAngle(atan2(_island[i]->_posY - _island[num_e[j]]->_posY, _island[i]->_posX - _island[num_e[j]]->_posX));

					double x1, y1, x2, y2, xy1, xy2, n_x1, n_y1, n_x2, n_y2;

					x1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->_posX - _island[num_e[j]]->_posX;
					y1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->_posY - _island[num_e[j]]->_posY;
					x2 = _island[i]->_posX - _island[num_e[j]]->_posX;
					y2 = _island[i]->_posY - _island[num_e[j]]->_posY;

					xy1 = sqrt(x1 * x1 + y1 * y1);
					xy2 = sqrt(x2 * x2 + y2 * y2);

					n_x1 = x1 / xy1;
					n_y1 = y1 / xy1;
					n_x2 = x2 / xy2;
					n_y2 = y2 / xy2;

					double dis_angle = atan2(n_x1 * n_y2 - n_x2 * n_y1, n_x1 * n_x2 + n_y1 * n_y2);

					int degree = (dis_angle * (180 / M_PI) < 0.0) ? (dis_angle * (180 / M_PI)) + 360 : dis_angle * (180 / M_PI);

					if (count == 0) {
						max_degree = degree;
						max_angle = _enemy[j]->GetAngle();
					}
					else {
						if (max_degree < degree) {
							max_angle = _enemy[j]->GetAngle();
							max_degree = degree;
						}
					}
					count++;
				}
				else
				{
					if (_enemy[j]->dis_number == 1) { // サルだったら
						int k;
						for (k = 0; k < ISLAND_NUM; k++) {
							if (_rope.GetConnectFlag(i, k))break;
						}
						if (k != ISLAND_NUM)continue; // ISLAND_NUMまで来なければつながっている
					}
					int k;
					for (k = 0; k < ENEMY_NUM; k++) {
						if (v_posX[j] == _enemy[k]->GetPosX() && v_posY[j] == _enemy[k]->GetPosY())break;
						//if (v_posX[j] == v_posX[k] && v_posY[j] == v_posY[k])break;
					}
					//if (k != ENEMY_NUM)continue;
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
			_enemy[j]->OnRopeModeFlag();
			_enemy[j]->SetAngle(max_angle);
			_enemy[j]->SetSpeed(cos(_enemy[j]->GetAngle()), sin(_enemy[j]->GetAngle()));
			_enemy[j]->SetLastTouchIslandNumber(num_e[j]);
		}
		else { // 折り返し移動処理
			bool lastCheck = 0;
			for (int k = 0; k < ISLAND_NUM; k++) {
				if (k == _enemy[j]->GetLastTouchIslandNumber())continue;
				if (_rope.GetConnectFlag(num_e[j], k)) {
					lastCheck = 1;
					break;
				}
			}
			if (lastCheck == 0 && _rope.GetConnectFlag(num_e[j], _enemy[j]->GetLastTouchIslandNumber()) && !_enemy[j]->GetRopeModeFlag()) {
				_enemy[j]->SetAngle(atan2(
					_island[_enemy[j]->GetLastTouchIslandNumber()]->_posY - _island[num_e[j]]->_posY, 
					_island[_enemy[j]->GetLastTouchIslandNumber()]->_posX - _island[num_e[j]]->_posX));
				_enemy[j]->SetSpeed(cos(_enemy[j]->GetAngle()), sin(_enemy[j]->GetAngle()));
				_enemy[j]->OnRopeModeFlag();
				_enemy[j]->SetLastTouchIslandNumber(num_e[j]);
			}
		}
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (_enemy[i]->GetJumpMoveFlag()) {
			if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && _enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
				_player.Damage();
			}
			else {
				int j;
				for (j = 0; j < ENEMY_NUM; j++) {
					if (v_posX[i] == _enemy[j]->GetPosX() && v_posY[i] == _enemy[j]->GetPosY())break;
				}
				if (j != ENEMY_NUM)continue;
				_enemy[i]->JumpMove(v_posX[i], v_posY[i]);
				_enemy[i]->OffJumpMoveFlag();
				_enemy[i]->SetLastTouchIslandNumber(num_e[i]);

				if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && _enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
					_player.Damage();
				}
			}
		}
		else {
			if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && (int)_enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
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
	//DrawFormatString(50, 200, GetColor(255, 255, 255), "%d", _time.GetGameTime());
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

void GameController::EnemySpawn(Enemy* enemy)
{
	int random = GetRand(7 - 1);
	int direction = 100;
	switch (random) {
	case 0:
		enemy->Instantiate(IslandInfo::Base_Island_PosX - direction - 200, IslandInfo::Base_Island_PosY - (direction * 5) + 200);
		break;
	case 1:
		enemy->Instantiate(IslandInfo::Base_Island_PosX - direction / 2 - 163, IslandInfo::Base_Island_PosY - (direction * 5) + 88);
		break;
	case 2:
		enemy->Instantiate(IslandInfo::Base_Island_PosX - direction / 2 - 65, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
		break;
	case 3:
		enemy->Instantiate(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 5) - 20);
		break;
	case 4:
		enemy->Instantiate(IslandInfo::Base_Island_PosX + direction / 2 + 65, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
		break;
	case 5:
		enemy->Instantiate(IslandInfo::Base_Island_PosX + direction / 2 + 163, IslandInfo::Base_Island_PosY - (direction * 5) + 88);
		break;
	case 6:
		enemy->Instantiate(IslandInfo::Base_Island_PosX + direction + 200, IslandInfo::Base_Island_PosY - (direction * 5) + 200);
		break;
	//case 7:
	//	enemy->Instantiate(580, 580);
	//	break;
	}
}