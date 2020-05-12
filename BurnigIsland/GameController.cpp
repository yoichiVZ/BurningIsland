#include <DxLib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "GameController.h"

#include "MyDrawTurn.h"

GameController::GameController()
{
	_gh_background = LoadGraph("Resource\\Image\\Haikei.png");
	_gh_background2 = LoadGraph("Resource\\Image\\makai2.png");
	_gh_cloud = LoadGraph("Resource\\Image\\KumoHaikei.png");
	LoadDivGraph("Resource\\Image\\kaminari.png", 5, 5, 1, 180, 700, _gh_thunder);
	LoadDivGraph("Resource\\Image\\kaminariUI.png", 6, 6, 1, 96, 96, _gh_thunderUI);
	_gh_UIbar = LoadGraph("Resource\\Image\\UI.png");
	_gh_hp = LoadGraph("Resource\\Image\\Life1.png");
	_gh_hp_damage = LoadGraph("Resource\\Image\\Life2.png");
	_gh_tuta_life_active = LoadGraph("Resource\\Image\\ge-ziUI2.png");
	_gh_tuta_life_inactive = LoadGraph("Resource\\Image\\ge-ziUI1.png");
	_gh_tuta = LoadGraph("Resource\\Image\\Tuta.png");
	_gh_tuta_top = LoadGraph("Resource\\Image\\Tutanomoto3.png");
	_gh_tuta_middle = LoadGraph("Resource\\Image\\Tutanomoto2.png");
	_gh_tuta_fire_top = LoadGraph("Resource\\Image\\moetuta2.png");
	_gh_tuta_fire_middle = LoadGraph("Resource\\Image\\moetuta1.png");
	_sh_gameplay = LoadSoundMem("Resource\\Sound\\gameplay.mp3");
	ChangeVolumeSoundMem(255 * 65 / 100, _sh_gameplay);
	_sh_thunder = LoadSoundMem("Resource\\Sound\\thunder.mp3");
	ChangeVolumeSoundMem(255 * 80 / 100, _sh_gameplay);
	GetGraphSize(_gh_background, &_background_width, &_background_height);
	GetGraphSize(_gh_cloud, &_cloud_width, &_cloud_height);
	GetGraphSize(_gh_thunder[0], &_thunder_width, &_thunder_height);
	GetGraphSize(_gh_tuta, &_tuta_width, &_tuta_height);
	GetGraphSize(_gh_tuta_top, &_tuta_top_width, &_tuta_top_height);
	GetGraphSize(_gh_tuta_middle, &_tuta_middle_width, &_tuta_middle_height);

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
	//for (i = 0; i < IslandInfo::Island_Num; i++) {
	//	_island_posX_data[i] = _island[i]->GetPosX();
	//	_island_posY_data[i] = _island[i]->GetPosY();
	//}
	//PositionSave();
	PositionLoad();
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
	//_enemyResponCount = 0;
	_enemyResponFlag = false;

	_cloud_posX = 0;
	_cloud_posY = 0;
	_cloud_speed_count = 0;

	_mouseCount_Left = 0;
	_mouseCount_Right = 0;
	_killCount = 0;
	_totalKillCount = 0;
	_wave = 0;
	_remainingEnemyCount = 0;
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_thunder_count[i] = 0;
		_animPos_thunder[i] = 0;
	}
	_animPos_thunderUI = 5;

	s_count = 0;
	right_count = 0;
	left_count = 0;
	up_count = 0;
	down_count = 0;
	_nowIsland = 0;
	_now_player_num = 0;

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i]->SetPosition(_island_posX_data[i], _island_posY_data[i]);
	}

	for (int i = 0; i < 4; i++) {
		_onth_flag[i] = 0;
	}
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
	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		StopSoundMem(_sh_gameplay);
		PlaySoundMem(_sh_gameplay, DX_PLAYTYPE_LOOP);
	}
	_time.TimeCourse();

	OnMouseButtonLeft();
	OnMouseButtonRight();
	OnSpaceButton();
	//if (CheckHitKey(KEY_INPUT_S))s_count++;
	//else s_count = 0;
	//if (CheckHitKey(KEY_INPUT_RIGHT))right_count++;
	//else right_count = 0;
	//if (CheckHitKey(KEY_INPUT_LEFT))left_count++;
	//else left_count = 0;
	//if (CheckHitKey(KEY_INPUT_UP))up_count++;
	//else up_count = 0;
	//if (CheckHitKey(KEY_INPUT_DOWN))down_count++;
	//else down_count = 0;

	//if (s_count == 1) {
	//	PositionSave();
	//}
	//if (right_count == 1 || (right_count > 10)) {
	//	_island[_nowIsland]->MoveX(1);
	//}
	//if (left_count == 1 || (left_count > 10)) {
	//	_island[_nowIsland]->MoveX(0);
	//}
	//if (up_count == 1 || (up_count > 10)) {
	//	_island[_nowIsland]->MoveY(0);
	//}
	//if (down_count == 1 || (down_count > 10)) {
	//	_island[_nowIsland]->MoveY(1);
	//}

	if (_spaceKeyCount == 1) {
		_sceneState = RESULT;
	}
	_cloud_speed_count++;
	if (_cloud_speed_count % 2 == 0) {
		_cloud_posX++;
	}
	if (_cloud_posX >= WindowInfo::Screen_Width) {
		_cloud_posX = 0;
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_thunder_count[i] > 0) {
			_thunder_count[i]--;
		}
	}

	if (_remainingEnemyCount <= 0) {
		int i;
		for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
			if (_enemy[i]->GetLiveFlag())break;
		}
		if (i == EnemyInfo::Enemy_Num) {
			_wave++;
			_remainingEnemyCount = _wave + 2;
			_enemyResponCount += 180;
		}
	}

	if (_fireReloadFlag) {
		_fireReloadCount++;
	}
	if (_fireReloadCount > FIRE_RELOAD_NUM) {
		_fireReloadCount = 0;
		_animPos_thunderUI = 5;
		_fireReloadFlag = false;
	}
	if (_fireReloadFlag && _fireReloadCount % (FIRE_RELOAD_NUM / 5) == 0) {
		_animPos_thunderUI++;
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
			EnemySpawn();
			_enemyResponFlag = false;
			
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_island[i]->PlayerStayCheck(_player.GetPosX(), _player.GetPosY())) {
			_now_player_num = i;
			//break;
		}
	}
	int num_e[EnemyInfo::Enemy_Num];
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		num_e[i] = 0;
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_island[j]->EnemyStayCheck(_enemy[i]->GetPosX(), _enemy[i]->GetPosY())) {
				num_e[i] = j;
				if (_island[j]->StateCheck_FIRE()) {
					_enemy[i]->Deth_Fire();
					_rope.Recovery();
					_killCount++;
					
				}
			}
		}
	}
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (i == _now_player_num)continue;
		if (_island[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
			bool connectCheck = false;
			for (int j = 0; j < IslandInfo::Island_Num; j++) {
				if (//_rope.GetConnectFlag(i, j) == 2	||		// 反対側からもロープをかけられる
					_rope.GetConnectFlag(_now_player_num, j) >= 3)	// 自分がいる島と繋がっているか
				{
					connectCheck = true;
				}
			}
			if (!connectCheck) {
				if (_island[_now_player_num]->GetPosX() == IslandInfo::Base_Island_PosX && _island[_now_player_num]->GetPosY() == IslandInfo::Base_Island_PosY) {

				}
				else {
					continue;
				}
			}
			if (_island[_now_player_num]->StateCheck_BURN())continue;
			//_island[num_p]->CrossCheck(_island[i]);
			if (_mouseCount_Left == 1) { // 左クリックした瞬間
				if (i == 0) {
					if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
						_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30 &&
						_rope.GetConnectFlag(_now_player_num, i) == 0)
					{
						if (_island[i]->StateCheck_BURN()) {
							_island[i]->Revival();
							_rope.Minus();
						}
						_rope.Connect(_now_player_num, i);
						_rope.Minus();
						continue;
					}
				}
				if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
					_rope.GetConnectFlag(_now_player_num, i) == 0)
				{
					if (_island[i]->StateCheck_BURN()) {
						_island[i]->Revival();
						_rope.Minus();
					}
					_rope.Connect(_now_player_num, i);
					_rope.Minus();
				}
			}
		}
	}
	if (_mouseCount_Left == 1) { // 左クリックした瞬間
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (i == 0) {
				if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30)
				{
					_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
					_nowIsland = i;
					break;
				}
			}
			if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
				_nowIsland = i;
			}
		}
	}
	//if (_mouseCount_Left > 10) { // 調整用
	//	for (int i = 0; i < IslandInfo::Island_Num; i++) {
	//		if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
	//			_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
	//		{
	//			_island[i]->SetPosition(_mousePosX_Left, _mousePosY_Left);
	//			break;
	//		}
	//	}
	//}
	if (_mouseCount_Right == 1) { // 右クリックした瞬間
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Right && _mousePosX_Right < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Right && _mousePosY_Right < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				if (i == 0)break;
				if (!_fireReloadFlag) {
					_island[i]->Burning();
					_fireReloadFlag = true;
					_animPos_thunderUI = 0;
					_killCount = 0;
					_thunder_count[i] = 25;
					PlaySoundMem(_sh_thunder, DX_PLAYTYPE_BACK);
					//_rope.AllRecovery();
				}
			}
		}
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(i, j) >= 3) {
				if (_island[i]->StateCheck_FIRE() && (!_rope.GetFireFlag(i, j) && !_rope.GetFireStartFlag(i, j))) {
					_rope.Ignition(i, j);
				}
				if (_island[j]->StateCheck_FIRE() && (!_rope.GetFireFlag(i, j) && !_rope.GetFireStartFlag(i, j))) {
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

		int v_dx = 1000, v_dy = 1000;
		int v_x = 0, v_y = 0;
		bool distanceFlag = false; // 範囲内に島があったらtrue
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (i == num_e[j])continue;

			if (_island[i]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
				distanceFlag = true;
				if (_rope.GetConnectFlag(num_e[j], i) >= 3 && !_enemy[j]->GetRopeModeFlag()) {
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
							if (_rope.GetConnectFlag(i, k) >= 1)break;
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
			else {
				if (_enemy[j]->_dis_number == 1) { // サルだったら
					int k;
					for (k = 0; k < IslandInfo::Island_Num; k++) {
						if (_rope.GetConnectFlag(i, k) >= 1)break;
					}
					if (k != IslandInfo::Island_Num)continue; // ISLAND_NUMまで来なければつながっている
				}
				auto x = abs(_island[i]->GetPosX() - v_posX[j]);
				auto y = abs(_island[i]->GetPosY() - v_posY[j]);
				auto xy = sqrt(x * x + y * y);
				if (xy < sqrt(v_dx * v_dx + v_dy * v_dy)) {
					v_dx = x;
					v_dy = y;
					v_x = _island[i]->GetPosX();
					v_y = _island[i]->GetPosY();
				}
			}
		}
		if (!distanceFlag) {
			v_posX[j] = v_x;
			v_posY[j] = v_y;
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
				if (_rope.GetConnectFlag(num_e[j], k) >= 3) {
					lastCheck = 1;
					break;
				}
			}
			if (lastCheck == 0 && _rope.GetConnectFlag(num_e[j], _enemy[j]->GetLastTouchIslandNumber()) >= 3 && !_enemy[j]->GetRopeModeFlag()) {
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
		if (_enemy[i]->GetJumpMoveFlag() && !_enemy[i]->_atackModeFlag) {
				int j;
				for (j = 0; j < EnemyInfo::Enemy_Num; j++) {
					if (v_posX[i] == _enemy[j]->GetPosX() && v_posY[i] == _enemy[j]->GetPosY())
						break;
				}
				if (j != EnemyInfo::Enemy_Num)continue;
				_enemy[i]->JumpMove(v_posX[i], v_posY[i]);
				_enemy[i]->OffJumpMoveFlag();
				_enemy[i]->SetLastTouchIslandNumber(num_e[i]);
		}
		if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && _enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
			_enemy[i]->Attack();
			_player.Damage();
			_enemy[i]->Deth();
			continue;
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
	DrawExtendGraph(_cloud_posX, _cloud_posY, _cloud_posX + WindowInfo::Screen_Width, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawExtendGraph(_cloud_posX - WindowInfo::Screen_Width, _cloud_posY, _cloud_posX, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawGraph(0, 0, _gh_background2, TRUE);
	MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_UIbar, 0.8f);
	//DrawGraph(_cloud_posX, _cloud_posY, _gh_cloud, TRUE);
	//DrawGraph(_cloud_posX - _cloud_width, _cloud_posY, _gh_cloud, TRUE);
	//DrawFormatString(10, 610, GetColor(0, 0, 0), "hp : %d", _player.GetHP());
	int playerHP = 0;
	for (int i = 0; i < PlayerInfo::Player_HP; i++) {
		if (playerHP < _player.GetHP()) {
			MyDrawTurn::Instance().SetDrawItem(820 + (70 * i) - 50, 766 - 50, _gh_hp, 0.81f);
		}
		else {
			MyDrawTurn::Instance().SetDrawItem(820 + (70 * i) - 50, 766 - 50, _gh_hp_damage, 0.81f);
		}
		playerHP++;
	}
	//if (!_fireReloadFlag) {
	//	DrawFormatString(10, 740, GetColor(0, 0, 0), "撃てる");
	//}
	DrawFormatString(10, 550, GetColor(0, 0, 0), "KILL : %d", _killCount);
	//DrawFormatString(10, 720, GetColor(0, 0, 0), "発射可能まで : %d", FIRE_RELOAD_NUM - _fireReloadCount);
	MyDrawTurn::Instance().SetDrawItem(42, 670, _gh_thunderUI[_animPos_thunderUI], 0.81f);
	DrawFormatString(10, 570, GetColor(0, 0, 0), "WAVE : %d", _wave);
	int ropeLife = 0;
	for (int i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		int nnnn = _rope.GetRopeLife();
		if (ropeLife < _rope.GetRopeLife()) {
			MyDrawTurn::Instance().SetDrawItem(280 + (50 * i) - 50, 766 - 50, _gh_tuta_life_active, 0.81f);
		}
		else {
			MyDrawTurn::Instance().SetDrawItem(280 + (50 * i) - 50, 766 - 50, _gh_tuta_life_inactive, 0.81f);
		}
		ropeLife++;
	}
	//DrawLine(300, 790, 300 + (_rope.GetRopeLife() * 40), 790, GetColor(255, 255, 100), 16);
	//for (int i = 1; i < _rope.GetRopeLife(); i++) {
	//	DrawLine(300 + i * 40, 782, 300 + i * 40, 798, GetColor(2055, 0, 0), 1);
	//}
	//DrawFormatString(50, 200, GetColor(255, 255, 255), "%d", _time.GetGameTime());
	for (int i = 1; i < IslandInfo::Island_Num; i++) {
		_island[i]->Draw();
	}
	_island[0]->Draw();
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_island[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
			bool connectCheck = false;
			for (int j = 0; j < IslandInfo::Island_Num; j++) {
				if (//_rope.GetConnectFlag(i, j) ||			// 反対側からもロープをかけられる
					_rope.GetConnectFlag(_now_player_num, j) >= 3)	// 自分がいる島と繋がっているか
				{
					connectCheck = true;
				}
			}
			if (!connectCheck) {
				if (_island[_now_player_num]->GetPosX() == IslandInfo::Base_Island_PosX && _island[_now_player_num]->GetPosY() == IslandInfo::Base_Island_PosY) {

				}
				else {
					continue;
				}
			}
			if (_island[_now_player_num]->StateCheck_BURN())continue;
			DrawLine(_player.GetPosX(), _player.GetPosY(), _island[i]->GetPosX(), _island[i]->GetPosY(), GetColor(150, 150, 150), 3);
		}
	}
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(i, j) == 1) {
				if (_rope._moveCount[i][j] == 0) {
					_rope._posX[i][j] = _island[i]->GetPosX();
					_rope._posY[i][j] = _island[i]->GetPosY();
				}
				_rope._moveCount[i][j]++;
				auto x = _island[j]->GetPosX() - _island[i]->GetPosX();
				auto y = _island[j]->GetPosY() - _island[i]->GetPosY();
				auto angle = atan2(y, x);
				_rope._posX[i][j] += cos(angle) * 5;
				_rope._posY[i][j] += sin(angle) * 5;
				auto dx = _rope._posX[i][j] - _island[i]->GetPosX();
				auto dy = _rope._posY[i][j] - _island[i]->GetPosY();
				//if (abs(_island[j]->GetPosX() - _rope._posX[i][j]) <= 3 && abs(_island[j]->GetPosY() - _rope._posY[i][j]) <= 3) {
				//	_rope._posX[i][j] = _island[j]->GetPosX();
				//	_rope._posY[i][j] = _island[j]->GetPosY();
				//	_rope.ConnectFinished(i, j);
				//}
				if (abs(dx) > abs(x) || abs(dy) > abs(y)) {
					_rope._posX[i][j] = _island[j]->GetPosX();
					_rope._posY[i][j] = _island[j]->GetPosY();
					_rope.ConnectFinished(i, j);
				}
				auto tmdistance = (_tuta_middle_height / 2.0) + (_tuta_top_height / 2.0);
				auto mmdistance = (_tuta_middle_height / 2.0) + (_tuta_middle_height / 2.0);
				auto mx = (int)_rope._posX[i][j] - (int)(tmdistance * cos(angle));
				auto my = (int)_rope._posY[i][j] - (int)(tmdistance * sin(angle));

				float priority = 0.3f;
				if (_island[i]->GetWidth() / 2 > abs(_rope._posX[i][j] - _island[i]->GetPosX())
					&& _island[i]->GetHeight() / 2 > abs(_rope._posY[i][j] - _island[i]->GetPosY()))
					priority = 0.19f;

				if (_rope.GetFireFlag(i, j)) {
					//DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 0, 0), 3);
				}
				else {
					//DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 255, 255), 3);
					//DrawRotaGraph(_island[i]->GetPosX() + x / 2, _island[i]->GetPosY() + y / 2, 1.0, angle, _gh_tuta, TRUE);
					//MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + (x / 2), _rope._posY[i][j] + (y / 2), _gh_tuta_top, 0.3f, DRAWTYPE_DRAWROTAGRAPH, angle);
					float priority = 0.3f;
					if (_island[i]->GetWidth() / 2 > abs(_rope._posX[i][j] - _island[i]->GetPosX())
						&& _island[i]->GetHeight() / 2 > abs(_rope._posY[i][j] - _island[i]->GetPosY()))
						priority = 0.19f;
					MyDrawTurn::Instance().SetDrawItem((int)_rope._posX[i][j], (int)_rope._posY[i][j], _gh_tuta_top, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					priority = 0.3f;
					if (dx >= abs((int)_rope._posX[i][j] - mx) || dy >= abs((int)_rope._posY[i][j] - my)) {
						if (_island[i]->GetWidth() / 2 > abs(mx - _island[i]->GetPosX())
							&& _island[i]->GetHeight() / 2 > abs(my - _island[i]->GetPosY()))
							priority = 0.19f;
						MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
						while (abs(mx - _island[i]->GetPosX()) >= abs(mmdistance * cos(angle)) && abs(my - _island[i]->GetPosY()) >= abs(mmdistance * sin(angle))) {
							priority = 0.3f;
							mx -= (int)mmdistance * cos(angle);
							my -= (int)mmdistance * sin(angle);
							if (_island[i]->GetWidth() / 2 > abs(mx - _island[i]->GetPosX())
								&& _island[i]->GetHeight() / 2 > abs(my - _island[i]->GetPosY()))
								priority = 0.19f;
							MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
						}
					}
				}
			}
			if (_rope.GetConnectFlag(i, j) == 3) {
				_rope._moveCount[i][j] = 0;
				auto x = _island[j]->GetPosX() - _island[i]->GetPosX();
				auto y = _island[j]->GetPosY() - _island[i]->GetPosY();
				auto angle = atan2(y, x);
				auto tmdistance = (_tuta_middle_height / 2.0) + (_tuta_top_height / 2.0);
				auto mmdistance = (_tuta_middle_height / 2.0) + (_tuta_middle_height / 2.0);
				auto mx = (int)_rope._posX[i][j] - (int)(tmdistance * cos(angle));
				auto my = (int)_rope._posY[i][j] - (int)(tmdistance * sin(angle));

				float priority = 0.3f;
				if (_island[i]->GetWidth() * 3 / 7 > abs(_rope._posX[i][j] - _island[i]->GetPosX())
					&& _island[i]->GetHeight() * 3 / 7 > abs(_rope._posY[i][j] - _island[i]->GetPosY()))
					priority = 0.19f;
				
				if (_rope.GetFireFlag(i, j)) {
					DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 0, 0), 3);

					MyDrawTurn::Instance().SetDrawItem((int)_rope._posX[i][j], (int)_rope._posY[i][j], _gh_tuta_fire_top, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					priority = 0.3f;
					if (abs((int)_rope._posX[i][j] - _island[i]->GetPosX()) >= abs((int)_rope._posX[i][j] - mx) || abs((int)_rope._posY[i][j] - _island[i]->GetPosY()) >= abs((int)_rope._posY[i][j] - my)) {
						if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
							&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
							priority = 0.19f;
						MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_fire_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
						while (abs(mx - _island[i]->GetPosX()) >= abs(mmdistance * cos(angle)) && abs(my - _island[i]->GetPosY()) >= abs(mmdistance * sin(angle))) {
							priority = 0.3f;
							mx -= (int)mmdistance * cos(angle);
							my -= (int)mmdistance * sin(angle);
							if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
								&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
								priority = 0.19f;
							MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_fire_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
						}
					}
				}
				else {
					DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 255, 255), 3);
					//DrawRotaGraph(_island[i]->GetPosX() + x / 2, _island[i]->GetPosY() + y / 2, 1.0, angle, _gh_tuta, TRUE);
					//MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + (x / 2), _rope._posY[i][j] + (y / 2), _gh_tuta_top, 0.3f, DRAWTYPE_DRAWROTAGRAPH, angle);
			
					MyDrawTurn::Instance().SetDrawItem((int)_rope._posX[i][j], (int)_rope._posY[i][j], _gh_tuta_top, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					priority = 0.3f;
					if (abs((int)_rope._posX[i][j] - _island[i]->GetPosX()) >= abs((int)_rope._posX[i][j] - mx) || abs((int)_rope._posY[i][j] - _island[i]->GetPosY()) >= abs((int)_rope._posY[i][j] - my)) {
						if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
							&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
							priority = 0.19f;
						MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
						while (abs(mx - _island[i]->GetPosX()) >= abs(mmdistance * cos(angle)) && abs(my - _island[i]->GetPosY()) >= abs(mmdistance * sin(angle))) {
							priority = 0.3f;
							mx -= (int)mmdistance * cos(angle);
							my -= (int)mmdistance * sin(angle);
							if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
								&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
								priority = 0.19f;
							MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
						}
					}
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
	int color = GetColor(255, 0, 0);
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		if (_thunder_count[i] > 0) {
			if (_thunder_count[i] % 5 == 0)_animPos_thunder[i]++;
			MyDrawTurn::Instance().SetDrawItem(_island[i]->GetPosX() - _thunder_width / 2, _island[i]->GetPosY() - _thunder_height + 10, _gh_thunder[_animPos_thunder[i]], 0.5f);
		}
		else {
			_animPos_thunder[i] = 0;
		}
	}
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

void GameController::EnemySpawn()
{
	int random = GetRand(3 - 1);
	int counter = 0;
	int direction = 100;
	while (counter < 3) {
		if (_remainingEnemyCount <= 0)break;
		_remainingEnemyCount--;
		int i;
		for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
			if (!_enemy[i]->GetLiveFlag())break;;
		}
		int x, y;
		switch (random) {
		case 0:
			if (counter == 0)x = -40, y = 40;
			if (counter == 1)x = 40, y = 0;
			if (counter == 2)x = -20, y = -30;
			_enemy[i]->SetFirstPosition(IslandInfo::Base_Island_PosX - 400 + x, IslandInfo::Base_Island_PosY - 510 + y);
			_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX - 400 - 200 + x, IslandInfo::Base_Island_PosY - 510 + y);
			break;
		case 1:
			if (counter == 0)x = -60, y = 0;
			if (counter == 1)x = 60, y = 0;
			if (counter == 2)x = 0, y = -10;
			_enemy[i]->SetFirstPosition(IslandInfo::Base_Island_PosX + x, IslandInfo::Base_Island_PosY - 600 + y);
			_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + x, IslandInfo::Base_Island_PosY - 600 - 100 + y);
			break;
		case 2:
			if (counter == 0)x = 40, y = 40;
			if (counter == 1)x = -40, y = 0;
			if (counter == 2)x = 20, y = -30;
			_enemy[i]->SetFirstPosition(IslandInfo::Base_Island_PosX + 400 + x, IslandInfo::Base_Island_PosY - 510 + y);
			_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + 400 + 200 + x, IslandInfo::Base_Island_PosY - 510 + y);
			break;
		default:
			break;
		//case 0:
		//	_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX - direction - 310 + 30 * counter, IslandInfo::Base_Island_PosY - (direction * 5) + 70);
		//	break;
		//case 1:
		//	_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX - direction / 2 - 210 + 30 * counter, IslandInfo::Base_Island_PosY - (direction * 5) + 10);
		//	break;
		//case 2:
		//	_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX - direction / 2 - 30 + 30 * counter, IslandInfo::Base_Island_PosY - (direction * 5) - 50);
		//	break;
		//	//case 3:
		//	//	enemy->Instantiate(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY - (direction * 5) - 20);
		//	//	break;
		//case 3:
		//	_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + direction / 2 + 50 + 30 * counter, IslandInfo::Base_Island_PosY - (direction * 5) - 50);
		//	break;
		//case 4:
		//	_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + direction / 2 + 220 + 30 * counter, IslandInfo::Base_Island_PosY - (direction * 5) + 10);
		//	break;
		//case 5:
		//	_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + direction + 320 + 30 * counter, IslandInfo::Base_Island_PosY - (direction * 5) + 70);
		//	break;
		//	//case 7:
		//	//	enemy->Instantiate(580, 580);
		//	//	break;
		}
		counter++;
	}
}

void GameController::PositionSave()
{
	FILE *fpx;
	fopen_s(&fpx, "Resource\\data\\PositionX.dat", "wb");

	if (fpx == NULL)return;

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island_posX_data[i] = _island[i]->GetPosX();
	}

	fwrite(&_island_posX_data, sizeof(_island_posX_data), 1, fpx);

	fclose(fpx);

	FILE *fpy;
	fopen_s(&fpy, "Resource\\data\\PositionY.dat", "wb");

	if (fpx == NULL)return;

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island_posY_data[i] = _island[i]->GetPosY();
	}

	fwrite(&_island_posY_data, sizeof(_island_posY_data), 1, fpy);

	fclose(fpy);
}

void GameController::PositionLoad()
{
	FILE *fpx;
	fopen_s(&fpx, "Resource\\data\\PositionX.dat", "rb");

	if (fpx == NULL) {
	}
	else{
		fread(&_island_posX_data, sizeof(_island_posX_data), 1, fpx);

		fclose(fpx);
	}

	FILE *fpy;
	fopen_s(&fpy, "Resource\\data\\PositionY.dat", "rb");

	if (fpy == NULL) {
	}
	else {
		fread(&_island_posY_data, sizeof(_island_posY_data), 1, fpy);

		fclose(fpy);
	}
}
