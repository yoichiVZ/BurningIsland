#include <DxLib.h>
#include <math.h>
#include "GameController.h"

GameController::GameController()
{
	_gh_background = LoadGraph("Resource\\Image\\Haikei.png");
	_gh_cloud = LoadGraph("Resource\\Image\\KumoHaikei.png");
	GetGraphSize(_gh_background, &_background_width, &_background_height);
	GetGraphSize(_gh_cloud, &_cloud_width, &_cloud_height);

	int i;
	for (i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i] = new Island();
		_island[i]->GetMyNumber(i);
	}
	for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i] = new Enemy();
	}
	for (i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i] = new Bullet();
	}
	_sceneState = GAMEPLAY;
	_spaceKeyCount = 0;
	Init();
}

GameController::~GameController()
{
	int i;
	for (i = 0; i < IslandInfo::Island_Num; i++) {
		delete _island[i];
	}
	for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
		delete _enemy[i];
	}
	for (i = 0; i < BulletInfo::Bullet_Num; i++) {
		delete _bullet[i];
	}
}

void GameController::Init()
{
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i]->Init();
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i]->Init();
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i]->Init();
	}
	_player.Init();
	_rope.Init();
	_time.Init();

	_fireReloadCount = 0;
	_fireReloadFlag = false;

	_enemyResponCount = 660;
	_enemyResponFlag = false;

	_cloud_posX = 0;
	_cloud_posY = 0;

	_mouseCount_Left = 0;
	_mouseCount_Right = 0;
	_killCount = 0;
	_totalKillCount = 0;
	_wave = 0;
	_remainingEnemyCount = 0;

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

	_island[22]->SetPosition(IslandInfo::Base_Island_PosX - direction - 170, IslandInfo::Base_Island_PosY - (direction * 4) + 205);
	_island[23]->SetPosition(IslandInfo::Base_Island_PosX - direction - 110, IslandInfo::Base_Island_PosY - (direction * 4) + 145);
	_island[24]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 115, IslandInfo::Base_Island_PosY - (direction * 4) + 100);
	_island[25]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 70, IslandInfo::Base_Island_PosY - (direction * 4) + 50);
	_island[26]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 15, IslandInfo::Base_Island_PosY - (direction * 4) + 20);
	_island[27]->SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 4) - 5);
	_island[28]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 15, IslandInfo::Base_Island_PosY - (direction * 4) + 20);
	_island[29]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 70, IslandInfo::Base_Island_PosY - (direction * 4) + 50);
	_island[30]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 115, IslandInfo::Base_Island_PosY - (direction * 4) + 100);
	_island[31]->SetPosition(IslandInfo::Base_Island_PosX + direction + 110, IslandInfo::Base_Island_PosY - (direction * 4) + 145);
	_island[32]->SetPosition(IslandInfo::Base_Island_PosX + direction + 170, IslandInfo::Base_Island_PosY - (direction * 4) + 205);

	_island[33]->SetPosition(IslandInfo::Base_Island_PosX - direction - 200, IslandInfo::Base_Island_PosY - (direction * 5) + 210);
	_island[34]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 163, IslandInfo::Base_Island_PosY - (direction * 5) + 100);
	_island[35]->SetPosition(IslandInfo::Base_Island_PosX - direction / 2 - 30, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
	//_island[36]->SetPosition(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 5) - 20);
	_island[37]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 30, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
	_island[38]->SetPosition(IslandInfo::Base_Island_PosX + direction / 2 + 163, IslandInfo::Base_Island_PosY - (direction * 5) + 100);
	_island[39]->SetPosition(IslandInfo::Base_Island_PosX + direction + 200, IslandInfo::Base_Island_PosY - (direction * 5) + 210);

	//_island[40]->SetPosition(IslandInfo::Base_Island_PosX + direction + 200, IslandInfo::Base_Island_PosY - (direction * 5) + 200);
}

void GameController::Title()
{
	OnSpaceButton();
	if (_spaceKeyCount == 1) {
		_sceneState = TUTORIAL;
	}
	DrawString(300, 300, "title", GetColor(255, 255, 255));
}

void GameController::Tutorial()
{
	OnSpaceButton();
	if (_spaceKeyCount == 1) {
		_sceneState = GAMEPLAY;
	}
	DrawString(300, 300, "tutorial", GetColor(255, 255, 255));
}

void GameController::GamePlay()
{
	_time.TimeCourse();

	OnMouseButtonLeft();
	OnMouseButtonRight();
	OnSpaceButton();
	if (_spaceKeyCount == 1) {
		_sceneState = RESULT;
	}

	_cloud_posX++;
	if (_cloud_posX >= WindowInfo::Screen_Width) {
		_cloud_posX = 0;
	}

	if (_remainingEnemyCount <= 0) {
		int i;
		for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
			if (_enemy[i]->GetLiveFlag())break;
		}
		if (i == EnemyInfo::Enemy_Num) {
			_wave++;
			_remainingEnemyCount = _wave;
			_enemyResponCount += 180;
		}
	}

	if (_fireReloadFlag) {
		_fireReloadCount++;
	}
	if (_fireReloadCount > FIRE_RELOAD_NUM) {
		_fireReloadCount = 0;
		_fireReloadFlag = false;
	}

	_enemyResponCount++;
	int levelCheck = 660;
	if (_wave <= 3) {
		levelCheck = 660;
	}
	else if (_wave <= 6) {
		levelCheck = 440;
	}
	else {
		levelCheck = 360;
	}

	if (_enemyResponCount > levelCheck) {
		_enemyResponCount = 0;
		_enemyResponFlag = true;
	}
	if (_enemyResponFlag) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
				if (_enemy[i]->GetLiveFlag())continue;
				EnemySpawn(_enemy[i]);
				_enemyResponFlag = false;
				break;
			}
		}
	}

	int num_p = 0;
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_island[i]->PlayerStayCheck(_player.GetPosX(), _player.GetPosY())) {
			num_p = i;
			break;
		}
	}
	int num_e[EnemyInfo::Enemy_Num];
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		num_e[i] = 0;
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag())continue;
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_island[j]->EnemyStayCheck(_enemy[i]->GetPosX(), _enemy[i]->GetPosY())) {
				num_e[i] = j;
				if (_island[j]->StateCheck_FIRE()) {
					_enemy[i]->Deth();
					_rope.Recovery();
					_killCount++;
					
				}
			}
		}
	}
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_island[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
			bool connectCheck = false;
			for (int j = 0; j < IslandInfo::Island_Num; j++) {
				if (_rope.GetConnectFlag(i, j)			// 反対側からもロープをかけられる
					|| _rope.GetConnectFlag(num_p, j))	// 自分がいる島と繋がっているか
				{
					connectCheck = true;
				}
			}
			if (!connectCheck) {
				if (_island[num_p]->GetPosX() == IslandInfo::Base_Island_PosX && _island[num_p]->GetPosY() == IslandInfo::Base_Island_PosY) {

				}
				else {
					continue;
				}
			}
			if (_island[num_p]->StateCheck_BURN())continue;
			_island[num_p]->CrossCheck(_island[i]);
			if (_mouseCount_Left == 1) { // 左クリックした瞬間
				if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
					!_rope.GetConnectFlag(num_p, i))
				{
					if (_island[i]->StateCheck_BURN()) {
						_island[i]->Revival();
						_rope.Minus();
					}
					_rope.Connect(num_p, i);
					_rope.Minus();
				}
			}
		}
	}

	if (_mouseCount_Left == 1) { // 左クリックした瞬間
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
			}
		}
	}
	if (_mouseCount_Right == 1) { // 右クリックした瞬間
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Right && _mousePosX_Right < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Right && _mousePosY_Right < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				if (!_fireReloadFlag) {
					_island[i]->Burning();
					_fireReloadFlag = true;
					_killCount = 0;
					//_rope.AllRecovery();
				}
			}
		}
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(i, j)) {
				if (_island[i]->StateCheck_FIRE()) {
					_rope.Ignition(i, j);
				}
				if (_island[j]->StateCheck_FIRE()) {
					_rope.Ignition(i, j);
				}
				if (_rope.GetFireFlag(i, j) && _island[i]->StateCheck_GRASS()) {
					_island[i]->Ignition();
				}
				if (_rope.GetFireFlag(i, j) && _island[j]->StateCheck_GRASS()) {
					_island[j]->Ignition();
				}
			}
		}
	}

	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag())continue;
		if (_enemy[i]->GetRopeModeFlag()) {
			for (int j = 0; j < IslandInfo::Island_Num; j++) {
				if (j == _enemy[i]->GetLastTouchIslandNumber())continue;
				if (_enemy[i]->GetPosX() <= _island[j]->GetPosX() + 2 && _enemy[i]->GetPosX() >= _island[j]->GetPosX() - 2
					&& _enemy[i]->GetPosY() <= _island[j]->GetPosY() + 2 && _enemy[i]->GetPosY() >= _island[j]->GetPosY() - 2) {
					_enemy[i]->OffRopeModeFlag();
					_enemy[i]->JumpMove(_island[j]->GetPosX(), _island[j]->GetPosY());
				}
			}
		}
	}

	int v_posX[EnemyInfo::Enemy_Num], v_posY[EnemyInfo::Enemy_Num];
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		v_posX[i] = _enemy[i]->GetPosX();
		v_posY[i] = _enemy[i]->GetPosY();
	}
	for (int j = 0; j < EnemyInfo::Enemy_Num; j++) {
		if (!_enemy[j]->GetLiveFlag())continue;

		int max_degree = 0;
		double max_angle = 0;
		int count = 0;
		int stackCheck[IslandInfo::Island_Num];
		for (int k = 0; k < IslandInfo::Island_Num; k++) {
			stackCheck[k] = 0;
		}

		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (i == num_e[j])continue;

			if (_island[i]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
				if (_rope.GetConnectFlag(num_e[j], i) && !_enemy[j]->GetRopeModeFlag()) {
					if (i == _enemy[j]->GetLastTouchIslandNumber())continue;
					if (_enemy[j]->_dis_number == 1)continue;

					_enemy[j]->SetAngle(atan2(_island[i]->GetPosY() - _island[num_e[j]]->GetPosY(), _island[i]->GetPosX() - _island[num_e[j]]->GetPosX()));

					double x1, y1, x2, y2, xy1, xy2, n_x1, n_y1, n_x2, n_y2;

					x1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosX() - _island[num_e[j]]->GetPosX();
					y1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosY() - _island[num_e[j]]->GetPosY();
					x2 = _island[i]->GetPosX() - _island[num_e[j]]->GetPosX();
					y2 = _island[i]->GetPosY() - _island[num_e[j]]->GetPosY();

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
					if (_enemy[j]->_dis_number == 1) { // サルだったら
						int k;
						for (k = 0; k < IslandInfo::Island_Num; k++) {
							if (_rope.GetConnectFlag(i, k))break;
						}
						if (k != IslandInfo::Island_Num)continue; // ISLAND_NUMまで来なければつながっている
					}
					int x = abs(_island[0]->GetPosX() - _island[i]->GetPosX());
					int y = abs(_island[0]->GetPosY() - _island[i]->GetPosY());
					int xx = abs(_island[0]->GetPosX() - v_posX[j]);
					int yy = abs(_island[0]->GetPosY() - v_posY[j]);
					int vx, vy;
					if (x * x + y * y < xx * xx + yy * yy) {
						vx = _island[i]->GetPosX();
						vy = _island[i]->GetPosY();
						int k;
						for (k = 0; k < EnemyInfo::Enemy_Num; k++) {
							if (vx == _enemy[k]->GetPosX() && vy == _enemy[k]->GetPosY())break;
						}
						if (k == EnemyInfo::Enemy_Num) {
							v_posX[j] = vx;
							v_posY[j] = vy;
						}
					}
				}
			}
		}
		if (_enemy[j]->_dis_number != 0)continue;
		if (count > 0) {
			_enemy[j]->OnRopeModeFlag();
			_enemy[j]->SetAngle(max_angle);
			_enemy[j]->SetSpeed(cos(_enemy[j]->GetAngle()), sin(_enemy[j]->GetAngle()));
			_enemy[j]->SetLastTouchIslandNumber(num_e[j]);
		}
		else{ // 折り返し移動処理
			bool lastCheck = 0;
			for (int k = 0; k < IslandInfo::Island_Num; k++) {
				if (k == _enemy[j]->GetLastTouchIslandNumber())continue;
				if (_rope.GetConnectFlag(num_e[j], k)) {
					lastCheck = 1;
					break;
				}
			}
			if (lastCheck == 0 && _rope.GetConnectFlag(num_e[j], _enemy[j]->GetLastTouchIslandNumber()) && !_enemy[j]->GetRopeModeFlag()) {
				_enemy[j]->SetAngle(atan2(
					_island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosY() - _island[num_e[j]]->GetPosY(),
					_island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosX() - _island[num_e[j]]->GetPosX()));
				_enemy[j]->SetSpeed(cos(_enemy[j]->GetAngle()), sin(_enemy[j]->GetAngle()));
				_enemy[j]->OnRopeModeFlag();
				_enemy[j]->SetLastTouchIslandNumber(num_e[j]);
			}
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && _enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
			_player.Damage();
			_enemy[i]->Deth();
			continue;
		}
		if (_enemy[i]->GetJumpMoveFlag() && !_enemy[i]->_atackModeFlag) {
				int j;
				for (j = 0; j < EnemyInfo::Enemy_Num; j++) {
					if (v_posX[i] == _enemy[j]->GetPosX() && v_posY[i] == _enemy[j]->GetPosY())break;
				}
				if (j != EnemyInfo::Enemy_Num)continue;
				_enemy[i]->JumpMove(v_posX[i], v_posY[i]);
				_enemy[i]->OffJumpMoveFlag();
				_enemy[i]->SetLastTouchIslandNumber(num_e[i]);
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (_enemy[i]->_dis_number != 2)continue;
		for (int j = 0; j < BulletInfo::Bullet_Num; j++) {
			if (_bullet[j]->GetLiveFlag())continue;
			if (_enemy[i]->_atackChargeflag) {
				_enemy[i]->Shot(_bullet[j], IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY);
				break;
			}
		}
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		if (!_bullet[i]->GetLiveFlag())continue;
		if (_bullet[i]->BaseHitCheck()) {
			_player.Damage();
			_bullet[i]->Deth();
		}
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_island[i]->ExtinguishedCheck()) {
			int j;
			for (j = 0; j < IslandInfo::Island_Num; j++) {
				if (_island[j]->StateCheck_FIRE())break;
			}
			if (j == IslandInfo::Island_Num) {
				while (_killCount >= 3) {
					_killCount -= 3;
					_totalKillCount += 3;
					_rope.AddMaxLife();
				}
				_totalKillCount += _killCount;
				_killCount = 0;
				_rope.AllRecovery();
			}
		}
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i]->Update();
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i]->Update();
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i]->Update();
	}
	_rope.Update();
	Draw();

	if (CheckHitKey(KEY_INPUT_R)) {
		Init();
	}
	if (!_player.GetLive()) {
		DrawFormatString(100, 10, GetColor(255, 255, 255), "GAMEOVER");
	}
}

void GameController::Result()
{
	OnSpaceButton();
	if (_spaceKeyCount == 1) {
		_sceneState = TITLE;
		Init();
	}
	DrawString(300, 300, "result", GetColor(255, 255, 255));
	DrawFormatString(300, 350, GetColor(255, 255, 255), "到達WAVE : %d", _wave);
}

void GameController::Draw()
{
	DrawGraph(0, 0, _gh_background, FALSE);
	//DrawGraph(_cloud_posX, _cloud_posY, _gh_cloud, TRUE);
	//DrawGraph(_cloud_posX - _cloud_width, _cloud_posY, _gh_cloud, TRUE);
	DrawExtendGraph(_cloud_posX, _cloud_posY, _cloud_posX + WindowInfo::Screen_Width, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawExtendGraph(_cloud_posX - WindowInfo::Screen_Width, _cloud_posY, _cloud_posX, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawFormatString(10, 10, GetColor(0, 0, 0), "hp : %d", _player.GetHP());
	if (!_fireReloadFlag) {
		DrawFormatString(10, 140, GetColor(0, 0, 0), "撃てる");
	}
	DrawFormatString(10, 100, GetColor(0, 0, 0), "KILL : %d", _killCount);
	DrawFormatString(10, 120, GetColor(0, 0, 0), "発射可能まで : %d", FIRE_RELOAD_NUM - _fireReloadCount);
	DrawFormatString(10, 160, GetColor(0, 0, 0), "WAVE : %d", _wave);
	DrawLine(300, 50, 300 + (_rope.GetRopeLife() * 40), 50, GetColor(255, 255, 100), 16);
	for (int i = 1; i < _rope.GetRopeLife(); i++) {
		DrawLine(300 + i * 40, 42, 300 + i * 40, 58, GetColor(2055, 0, 0), 1);
	}
	//DrawFormatString(50, 200, GetColor(255, 255, 255), "%d", _time.GetGameTime());
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i]->Draw();
	}
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(i, j)) {
				if (_rope.GetFireFlag(i, j)) {
					DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 0, 0), 3);
				}
				else {
					DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 255, 255), 3);
				}
			}
			DrawFormatString(_island[i]->GetPosX(), _island[i]->GetPosY(), GetColor(0, 0, 0), "%d", i);
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i]->Draw();
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i]->Draw();
	}
	_player.Draw();
}

void GameController::All()
{
	switch (_sceneState) {
	case TITLE:   
		Title();
		break;
	case TUTORIAL:
		Tutorial();
		break;
	case GAMEPLAY:
		GamePlay();
		break;
	case RESULT:  
		Result();
		break;
	default:
		GamePlay();
		break;
	}
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

int GameController::OnSpaceButton()
{
	if (CheckHitKey(KEY_INPUT_SPACE) == 0) {
		if (_spaceKeyCount > 0) {
			_spaceKeyCount = -1;
			return _spaceKeyCount;
		}
		else {
			_spaceKeyCount = 0;
			return _spaceKeyCount;
		}
	}
	else {
		_spaceKeyCount++;
		return _spaceKeyCount;
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
	if (_remainingEnemyCount <= 0)return;
	_remainingEnemyCount--;
	int random = GetRand(6 - 1);
	int direction = 100;
	switch (random) {
	case 0:
		enemy->Instantiate(IslandInfo::Base_Island_PosX - direction - 200, IslandInfo::Base_Island_PosY - (direction * 5) + 210);
		break;
	case 1:
		enemy->Instantiate(IslandInfo::Base_Island_PosX - direction / 2 - 163, IslandInfo::Base_Island_PosY - (direction * 5) + 100);
		break;
	case 2:
		enemy->Instantiate(IslandInfo::Base_Island_PosX - direction / 2 - 30, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
		break;
	//case 3:
	//	enemy->Instantiate(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 5) - 20);
	//	break;
	case 3:
		enemy->Instantiate(IslandInfo::Base_Island_PosX + direction / 2 + 30, IslandInfo::Base_Island_PosY - (direction * 5) + 15);
		break;
	case 4:
		enemy->Instantiate(IslandInfo::Base_Island_PosX + direction / 2 + 163, IslandInfo::Base_Island_PosY - (direction * 5) + 100);
		break;
	case 5:
		enemy->Instantiate(IslandInfo::Base_Island_PosX + direction + 200, IslandInfo::Base_Island_PosY - (direction * 5) + 210);
		break;
	//case 7:
	//	enemy->Instantiate(580, 580);
	//	break;
	}
}