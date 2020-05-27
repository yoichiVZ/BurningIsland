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
	_gh_tutorial[0] = LoadGraph("Resource\\Image\\tutolial1.png");
	_gh_tutorial[1] = LoadGraph("Resource\\Image\\tutolial2.png");
	_gh_tutorial[2] = LoadGraph("Resource\\Image\\tutolial3.png");
	_gh_tutorial[3] = LoadGraph("Resource\\Image\\tutolial4.png");
	_gh_title = LoadGraph("Resource\\Image\\Title.png");
	_gh_title_background = LoadGraph("Resource\\Image\\TitleHaikei.png");
	_gh_title_start = LoadGraph("Resource\\Image\\StartButton.png");
	_gh_title_tutorial = LoadGraph("Resource\\Image\\TutolialButton.png");
	_gh_title_cloud[0] = LoadGraph("Resource\\Image\\Cloud1.png");
	_gh_title_cloud[1] = LoadGraph("Resource\\Image\\Cloud1Revers.png");
	_gh_title_cloud[2] = LoadGraph("Resource\\Image\\Cloud3.png");
	_gh_title_cloud[3] = LoadGraph("Resource\\Image\\Cloud2Revers.png");
	LoadDivGraph("Resource\\Image\\kaminari.png", 5, 5, 1, 180, 700, _gh_thunder);
	LoadDivGraph("Resource\\Image\\kaminariUI.png", 6, 6, 1, 96, 96, _gh_thunderUI);
	_gh_UIbar = LoadGraph("Resource\\Image\\UI.png");
	_gh_UIStart = LoadGraph("Resource\\Image\\Start.png");
	//_gh_hp = LoadGraph("Resource\\Image\\Life1.png");
	_gh_hp[0] = LoadGraph("Resource\\Image\\Baria1.png");
	_gh_hp[1] = LoadGraph("Resource\\Image\\Baria2.png");
	_gh_hp[2] = LoadGraph("Resource\\Image\\Baria3.png");
	_gh_hp_damage = LoadGraph("Resource\\Image\\Life2.png");
	_gh_wave = LoadGraph("Resource\\Image\\WAVE.png");
	_gh_tuta_life_active = LoadGraph("Resource\\Image\\ge-ziUI2.png");
	_gh_tuta_life_inactive = LoadGraph("Resource\\Image\\ge-ziUI1.png");
	//_gh_tuta = LoadGraph("Resource\\Image\\Tuta.png");
	//_gh_tuta_top = LoadGraph("Resource\\Image\\Tutanomoto3.png");
	//_gh_tuta_middle = LoadGraph("Resource\\Image\\Tutanomoto2.png");
	//_gh_tuta_fire_top = LoadGraph("Resource\\Image\\moetuta2.png");
	//_gh_tuta_fire_middle = LoadGraph("Resource\\Image\\moetuta1.png");
	LoadDivGraph("Resource\\Image\\TutaAnime.png", 10, 10, 1, 40, 100, _gh_tuta_anim);
	LoadDivGraph("Resource\\Image\\MoeruTuta1.png", 6, 6, 1, 40, 100, _gh_tuta_fire1_anim);
	LoadDivGraph("Resource\\Image\\MoeruTuta2.png", 6, 6, 1, 40, 100, _gh_tuta_fire2_anim);
	_sh_title = LoadSoundMem("Resource\\Sound\\title.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_title);
	_sh_tutorial = LoadSoundMem("Resource\\Sound\\tutorial.mp3");
	ChangeVolumeSoundMem(255 * 25 / 100, _sh_tutorial);
	_sh_gameplay = LoadSoundMem("Resource\\Sound\\gameplay.mp3");
	ChangeVolumeSoundMem(255 * 25 / 100, _sh_gameplay);
	_sh_result = LoadSoundMem("Resource\\Sound\\result.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_result);
	_sh_thunder = LoadSoundMem("Resource\\Sound\\thunder.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_thunder);
	_sh_thunderCharge = LoadSoundMem("Resource\\Sound\\thunderCharge.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_thunderCharge);
	_sh_click = LoadSoundMem("Resource\\Sound\\Click.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_click);
	_sh_tuta_imposible = LoadSoundMem("Resource\\Sound\\tuta_imposible.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_tuta_imposible);
	GetGraphSize(_gh_background, &_background_width, &_background_height);
	GetGraphSize(_gh_cloud, &_cloud_width, &_cloud_height);
	GetGraphSize(_gh_thunder[0], &_thunder_width, &_thunder_height);
	//GetGraphSize(_gh_tuta, &_tuta_width, &_tuta_height);
	//GetGraphSize(_gh_tuta_top, &_tuta_top_width, &_tuta_top_height);
	//GetGraphSize(_gh_tuta_middle, &_tuta_middle_width, &_tuta_middle_height);
	GetGraphSize(_gh_tuta_anim[0], &_tuta_width, &_tuta_height);
	GetGraphSize(_gh_hp[0], &_hp_width, &_hp_height);

	int i;
	for (i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i] = new Island();
		_island[i]->GetMyNumber(i);
	}
	for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i] = new Enemy();
		_killCountUI[i] = new KillCountUI;
	}
	for (i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i] = new Bullet();
	}
	_sceneState = TITLE;
	_spaceKeyCount = 0;
	//for (i = 0; i < IslandInfo::Island_Num; i++) {
	//	_island_posX_data[i] = _island[i]->GetPosX();
	//	_island_posY_data[i] = _island[i]->GetPosY();
	//}
	//PositionSave();
	PositionLoad();
	EnemySpawnNumberInit();
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
		delete _killCountUI[i];
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
		_killCountUI[i]->Init();
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i]->Init();
	}
	_player.Init();
	_rope.Init();
	_time.Init();
	_ropeLifeUpEffect.Init();
	_thunderChargeUI.Init();

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
	_UIstartCount = 0;
	_tutorialCount = 0;
	for (int i = 0; i < 4; i++) {
		_pos_cloud[i] = 0;
	}
	_posCount = 0;

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_thunder_count[i] = 0;
		_animPos_thunder[i] = 0;
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			_animPos_tuta[i][j] = 0;
			_animPos_tuta_fire1[i][j] = 0;
			_animPos_tuta_fire2[i][j] = 0;
			_animCount_tuta_fire1[i][j] = 0;
			_animCount_tuta_fire2[i][j] = 0;
		}
	}
	_animPos_thunderUI = 5;

	s_count = 0;
	right_count = 0;
	left_count = 0;
	up_count = 0;
	down_count = 0;
	_nowIsland = 0;
	_now_player_num = 0;

	_enemySpawnCount = 0;


	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i]->SetPosition(_island_posX_data[i], _island_posY_data[i]);
	}

	for (int i = 0; i < 4; i++) {
		_onth_flag[i] = 0;
	}
}

void GameController::Title()
{
	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		StopSoundMem(_sh_result);
		StopSoundMem(_sh_tutorial);
		PlaySoundMem(_sh_title, DX_PLAYTYPE_LOOP);
	}
	MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_title_background, 0.1f);
	MyDrawTurn::Instance().SetDrawItem(100, 250, _gh_title, 0.5f);
	int startWidth = 282;
	int startHeight = 79;
	int mousePosX, mousePosY;
	GetMousePoint(&mousePosX, &mousePosY);
	if (150 < mousePosX && 150 + startWidth > mousePosX &&
		550 < mousePosY && 550 + startHeight > mousePosY) {
		MyDrawTurn::Instance().SetDrawItem(150 + startWidth / 2, 550 + startHeight / 2, _gh_title_start, 0.5f,DRAWTYPE_DRAWROTAGRAPH,1.2);
		if (_mouseCount_Left == -1) {
			PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
			_sceneState = GAMEPLAY;
		}
	}
	else {
		MyDrawTurn::Instance().SetDrawItem(150 + startWidth / 2, 550 + startHeight / 2, _gh_title_start, 0.5f, DRAWTYPE_DRAWROTAGRAPH, 1);
	}

	int tutorialWidth = 412;
	int tutorialHeight = 89;
	if (480 < mousePosX && 480 + tutorialWidth > mousePosX &&
		550 < mousePosY && 550 + tutorialHeight > mousePosY) {
		MyDrawTurn::Instance().SetDrawItem(480 + tutorialWidth / 2, 550 + tutorialHeight / 2, _gh_title_tutorial, 0.5f, DRAWTYPE_DRAWROTAGRAPH, 1.2);
		if (_mouseCount_Left == -1) {
			_onth_flag[_sceneState] = 0;
			PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
			_sceneState = TUTORIAL;
		}
	}
	else {
		MyDrawTurn::Instance().SetDrawItem(480 + tutorialWidth / 2, 550 + tutorialHeight / 2, _gh_title_tutorial, 0.5f, DRAWTYPE_DRAWROTAGRAPH, 1);
	}
	
	_posCount++;
	for (int i = 0; i < 4; i++) {
		if (_posCount % 6 == 0) {
			if (i == 1 || i == 3)
				_pos_cloud[i] -= 1 * (4 - i);
			else
				_pos_cloud[i] += 1 * (4 - i);
		}
	}

	if (_pos_cloud[0] > WindowInfo::Screen_Width) {
		_pos_cloud[0] = 0 - 1149;
	}
	if (_pos_cloud[1] + 1149 < 0) {
		_pos_cloud[1] = WindowInfo::Screen_Width;
	}
	if (_pos_cloud[2] > WindowInfo::Screen_Width) {
		_pos_cloud[2] = 0 - 528;
	}
	if (_pos_cloud[3] + 522 < 0) {
		_pos_cloud[3] = WindowInfo::Screen_Width;
	}

	MyDrawTurn::Instance().SetDrawItem(_pos_cloud[0], 550, _gh_title_cloud[0], 0.25f);
	MyDrawTurn::Instance().SetDrawItem(_pos_cloud[1], 650, _gh_title_cloud[1], 0.24f);
	MyDrawTurn::Instance().SetDrawItem(_pos_cloud[2], 400, _gh_title_cloud[2], 0.23f);
	MyDrawTurn::Instance().SetDrawItem(_pos_cloud[3], 350, _gh_title_cloud[3], 0.22f);

	//MyDrawTurn::Instance().SetDrawItem(480, 550, _gh_title_tutorial, 0.5f);
	//DrawString(300, 300, "title", GetColor(255, 255, 255));
	//DrawString(300, 340, "OnClick", GetColor(255, 255, 255));
}

void GameController::Tutorial()
{
	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		_tutorialCount = 0;
		StopSoundMem(_sh_title);
		PlaySoundMem(_sh_tutorial, DX_PLAYTYPE_LOOP);
	}
	if (_mouseCount_Left == -1) {
		_tutorialCount++;
	}
	if (_tutorialCount >= 4) {
		_onth_flag[_sceneState] = 0;
		PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
		_sceneState = TITLE;
	}
	else {
		MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_cloud, 0.5f);
		MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_tutorial[_tutorialCount], 0.5f);
	}
	//DrawString(300, 300, "tutorial", GetColor(255, 255, 255));
	//DrawString(300, 330, "Left Click : 島移動、ロープをかける", GetColor(255, 255, 255));
	//DrawString(300, 360, "Right Click : 雷を落とす", GetColor(255, 255, 255));
	//DrawString(300, 400, "OnClick", GetColor(255, 255, 255));
}

void GameController::GamePlay()
{
	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		StopSoundMem(_sh_title);
		PlaySoundMem(_sh_gameplay, DX_PLAYTYPE_LOOP);
	}
	_time.TimeCourse();

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

	//if (_spaceKeyCount == 1) {
	//	_sceneState = RESULT;
	//}
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
			//_remainingEnemyCount = _wave + 2;
			switch (_wave) {
			case 1:
				_remainingEnemyCount = 3;
				break;
			case 2:
				_remainingEnemyCount = 14;
				break;
			case 3:
				_remainingEnemyCount = 10;
				break;
			case 4:
				_remainingEnemyCount = 17;
				break;
			case 5:
				_remainingEnemyCount = 15;
				break;
			case 6:
				_remainingEnemyCount = 15;
				break;
			case 7:
				_remainingEnemyCount = 15;
				break;
			case 8:
				_remainingEnemyCount = 18;
				break;
			case 9:
				_remainingEnemyCount = 21;
				break;
			case 10:
				_remainingEnemyCount = 30;
				break;
			case 11:
				_sceneState = RESULT;
				break;
			}
			_enemyResponCount += 1000;
		}
	}

	if (_fireReloadFlag) {
		_fireReloadCount++;
	}
	if (_fireReloadCount > FIRE_RELOAD_NUM) {
		PlaySoundMem(_sh_thunderCharge, DX_PLAYTYPE_BACK);
		_fireReloadCount = 0;
		_animPos_thunderUI = 5;
		_fireReloadFlag = false;
		_thunderChargeUI.SetActive(true);
	}
	if (_fireReloadFlag && _fireReloadCount % (FIRE_RELOAD_NUM / 5) == 0) {
		_animPos_thunderUI++;
	}

	_enemyResponCount++;
	int levelCheck = 440;
	if (_wave <= 3) {
		levelCheck = 440;
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
					//_rope.Recovery();
					_killCount++;
					_killCountUI[i]->SetActive(_enemy[i]->GetPosX(), _enemy[i]->GetPosY(), _killCount);
					if (_killCount >= 3 && _rope.GetMaxRopeLife() < RopeInfo::Rope_MaxLife) {
						if (!_ropeLifeUpEffect.GetActiveFlag()) {
							_ropeLifeUpEffect.SetEffect(_enemy[i]->GetPosX(), _enemy[i]->GetPosY(), 240 + (40 * _rope.GetMaxRopeLife()), 766);
						}
					}
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
					_rope.GetConnectFlag(_now_player_num, j) >= 1)	// 自分がいる島と繋がっているか
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
						//if (_island[i]->StateCheck_BURN()) {
						//	_island[i]->Revival();
						//	_rope.Minus();
						//}
						if (_rope.GetRopeLife() > 0) {
							_rope.Connect(_now_player_num, i);
							_rope.Minus();
							continue;
						}
						else {
							if (CheckSoundMem(_sh_tuta_imposible) == 0)
								PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
						}
					}
				}
				if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
					_rope.GetConnectFlag(_now_player_num, i) == 0)
				{
					if (_rope.GetRopeLife() > 0) {
						if (_island[i]->StateCheck_BURN()) {
							_island[i]->Revival();
							_rope.Minus();
						}
						_rope.Connect(_now_player_num, i);
						_rope.Minus();
					}
					else {
						if (CheckSoundMem(_sh_tuta_imposible) == 0)
							PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
					}
				}
			}
			else if (_mouseCount_Left > 1) { // 左クリックしてる間
				if (i == 0) {
					if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
						_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30 &&
						_rope.GetConnectFlag(_now_player_num, i) == 0)
					{
						//if (_island[i]->StateCheck_BURN()) {
						//	_island[i]->Revival();
						//	_rope.Minus();
						//}
						if (_rope.GetRopeLife() > 0) {
							_rope.Connect(_now_player_num, i);
							_rope.Minus();
							continue;
						}
						else {
							if (CheckSoundMem(_sh_tuta_imposible) == 0)
								PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
						}
					}
				}
				if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
					_rope.GetConnectFlag(_now_player_num, i) == 0)
				{
					if (_rope.GetRopeLife() > 0) {
						if (_island[i]->StateCheck_BURN()) {
							_island[i]->Revival();
							_rope.Minus();
						}
						_rope.Connect(_now_player_num, i);
						_rope.Minus();
					}
					else {
						if (CheckSoundMem(_sh_tuta_imposible) == 0)
							PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
					}
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
	else if (_mouseCount_Left > 1) { // 左クリックしてる間
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
					_thunderChargeUI.SetActive(false);
					PlaySoundMem(_sh_thunder, DX_PLAYTYPE_BACK);
					//_rope.AllRecovery();
					for (int j = 0; j < EnemyInfo::Enemy_Num; j++) {
						if (num_e[j] == i && !_enemy[j]->GetJumpNowFlag() && !_enemy[j]->GetRopeModeFlag()) {
							_enemy[j]->Deth_Fire();
							_killCount++;
							_killCountUI[j]->SetActive(_enemy[j]->GetPosX(), _enemy[j]->GetPosY(), _killCount);
							if (_killCount >= 3 && _rope.GetMaxRopeLife() < RopeInfo::Rope_MaxLife) {
								if (!_ropeLifeUpEffect.GetActiveFlag()) {
									_ropeLifeUpEffect.SetEffect(_enemy[j]->GetPosX(), _enemy[j]->GetPosY(),  240 + (40 * _rope.GetMaxRopeLife()), 766);
								}
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(i, j) >= 1) {
				if (_island[i]->StateCheck_FIRE() && (_rope.GetFireFlag(i, j) == 0 && _rope.GetFireStartFlag(i, j) == 0)) {
					_rope.Ignition(i, j);
				}
				if (_island[j]->StateCheck_FIRE() && (_rope.GetFireFlag(i, j) == 0 && _rope.GetFireStartFlag(i, j) == 0)) {
					_rope.Ignition(j, i);
				}
				if (_rope.GetFireFlag(i, j) != 0 && _island[i]->StateCheck_GRASS() && _island[i]->GetFireStartflag() == 0) {
					if(i != 0)
						_island[i]->Ignition();
				}
				if (_rope.GetFireFlag(i, j) != 0 && _island[j]->StateCheck_GRASS() && _island[j]->GetFireStartflag() == 0) {
					if(j != 0)
						_island[j]->Ignition();
				}
			}
		}
	}

	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
		if (_enemy[i]->GetRopeModeFlag()) {
			for (int j = 0; j < IslandInfo::Island_Num; j++) {
				if (j == _enemy[i]->GetLastTouchIslandNumber())continue;
				if (_enemy[i]->GetPosX() <= _island[j]->GetPosX() + 2 && _enemy[i]->GetPosX() >= _island[j]->GetPosX() - 2
					&& _enemy[i]->GetPosY() <= _island[j]->GetPosY() + 2 && _enemy[i]->GetPosY() >= _island[j]->GetPosY() - 2) {
					_enemy[i]->OffRopeModeFlag();
					//_enemy[i]->JumpMove(_island[j]->GetPosX(), _island[j]->GetPosY());
					//_enemy[i]->JumpStart(_island[j]->GetPosX(), _island[j]->GetPosY() - 10);
				}
			}
		}
	}

	//int v_posX[EnemyInfo::Enemy_Num], v_posY[EnemyInfo::Enemy_Num];
	//int v_islandNumber[EnemyInfo::Enemy_Num];
	//for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
	//	v_posX[i] = _enemy[i]->GetPosX();
	//	v_posY[i] = _enemy[i]->GetPosY();
	//	v_islandNumber[i] = -1;
	//}
	for (int j = 0; j < EnemyInfo::Enemy_Num; j++) {
		if (!_enemy[j]->GetLiveFlag() || _enemy[j]->GetDethDelayFlag())continue;
		if (_enemy[j]->GetFirstMoveFlag())continue;
		if (_enemy[j]->GetJumpNowFlag())continue;

		int max_degree = 0;
		double max_angle = 0;
		int count = 0;
		//int stackCheck[IslandInfo::Island_Num];
		//for (int k = 0; k < IslandInfo::Island_Num; k++) {
		//	stackCheck[k] = 0;
		//}

		int v_dx = 1000, v_dy = 1000;
		int v_x = _enemy[j]->GetNextJumpPosX(), v_y = _enemy[j]->GetNextJumpPosY();
		int v_n = 0;
		bool distanceFlag = false; // 範囲内に島があったらtrue

		//for (int k = 0; k < IslandInfo::Island_Num; k++) {
		//	if(_island[num_e[j]]->EnemyDistanseCheck())
		//}

		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (i == num_e[j])continue;
			
			for (int k = 0; k < IslandInfo::Island_Num; k++) {
				if (_island[i]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
					distanceFlag = true;
				}
			}

			if (_island[i]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
				//distanceFlag = true;
				if (_rope.GetConnectFlag(num_e[j], i) >= 3 && !_enemy[j]->GetRopeModeFlag()) {
					if (i == _enemy[j]->GetLastTouchIslandNumber())continue;
					if (_enemy[j]->_dis_number != ENEMYTYPE_SLIME)continue;

					_enemy[j]->SetAngle(atan2(_island[i]->GetPosY() - _island[num_e[j]]->GetPosY(), _island[i]->GetPosX() - _island[num_e[j]]->GetPosX()));

					//double x1, y1, x2, y2, xy1, xy2, n_x1, n_y1, n_x2, n_y2;

					auto x1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosX() - _island[num_e[j]]->GetPosX();
					auto y1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosY() - _island[num_e[j]]->GetPosY();
					auto x2 = _island[i]->GetPosX() - _island[num_e[j]]->GetPosX();
					auto y2 = _island[i]->GetPosY() - _island[num_e[j]]->GetPosY();

					auto xy1 = sqrt(x1 * x1 + y1 * y1);
					auto xy2 = sqrt(x2 * x2 + y2 * y2);

					auto n_x1 = x1 / xy1;
					auto n_y1 = y1 / xy1;
					auto n_x2 = x2 / xy2;
					auto n_y2 = y2 / xy2;

					auto dis_angle = atan2(n_x1 * n_y2 - n_x2 * n_y1, n_x1 * n_x2 + n_y1 * n_y2);

					auto degree = (dis_angle * (180 / M_PI) < 0.0) ? (dis_angle * (180 / M_PI)) + 360 : dis_angle * (180 / M_PI);

					if (count == 0) {
						max_degree = degree;
						max_angle = _enemy[j]->GetAngle();
					}
					else {
						if (max_degree < degree) {
							max_angle = _enemy[j]->GetAngle();
							max_degree = degree;
							//v_n = i;
						}
					}
					count++;
				}
				else
				{
					if (_enemy[j]->_onthThinkFlag == 1)continue;

					int x = abs(_island[0]->GetPosX() - _island[i]->GetPosX());
					int y = abs(_island[0]->GetPosY() - _island[i]->GetPosY());
					//int xx = abs(_island[0]->GetPosX() - v_posX[j]);
					//int yy = abs(_island[0]->GetPosY() - v_posY[j]);
					int xx = abs(_island[0]->GetPosX() - _enemy[j]->GetNextJumpPosX());
					int yy = abs(_island[0]->GetPosY() - _enemy[j]->GetNextJumpPosY());
					//int vx, vy;
					if (x * x + y * y < xx * xx + yy * yy) {
						if (_enemy[j]->_dis_number == ENEMYTYPE_MONKEY && i != 0) { // サルだったら
							int k;
							for (k = 0; k < IslandInfo::Island_Num; k++) {
								if (_rope.GetConnectFlag(i, k) >= 1)break;
							}
							//_enemy[j]->SetPerceiveFlag(false);
							if (k != IslandInfo::Island_Num) { // ISLAND_NUMまで来なければつながっている
								_enemy[j]->SetPerceiveFlag(true);
								continue;
							}
						}

						//vx = _island[i]->GetPosX();
						//vy = _island[i]->GetPosY();
						int k;
						for (k = 0; k < EnemyInfo::Enemy_Num; k++) {
							if (j == k)continue;
							if (!_enemy[k]->GetLiveFlag() || _enemy[k]->GetDethDelayFlag())continue;
							if (_enemy[k]->GetRopeModeFlag())continue;
							if (_island[i]->GetPosX() == _enemy[k]->GetPosX() && _island[i]->GetPosY() == _enemy[k]->GetPosY())break;
							if (_island[i]->GetPosX() == _enemy[k]->GetNextJumpPosX() && _island[i]->GetPosY() == _enemy[k]->GetNextJumpPosY())
								break;
						}
						if (k == EnemyInfo::Enemy_Num) {
							//v_posX[j] = vx;
							//v_posY[j] = vy;
							//v_islandNumber[j] = i;
							_enemy[j]->SetNextJumpInfo(_island[i]->GetPosX(), _island[i]->GetPosY(), i);
						}
					}
				}
			}
			else if(!distanceFlag){
				if (_enemy[j]->_onthThinkFlag == 1)continue;
			    
				//auto x = abs(_island[i]->GetPosX() - v_posX[j]);
				//auto y = abs(_island[i]->GetPosY() - v_posY[j]);
				auto x = abs(_island[i]->GetPosX() - _enemy[j]->GetPosX());
				auto y = abs(_island[i]->GetPosY() - _enemy[j]->GetPosY());
				auto xy = sqrt(x * x + y * y);
				if (xy < sqrt(v_dx * v_dx + v_dy * v_dy)) {
					if (_enemy[j]->_dis_number == ENEMYTYPE_MONKEY && i != 0) { // サルだったら
						int k;
						for (k = 0; k < IslandInfo::Island_Num; k++) {
							if (_rope.GetConnectFlag(i, k) >= 1)break;
						}
						if (k != IslandInfo::Island_Num) { // ISLAND_NUMまで来なければつながっている
							//_enemy[j]->SetPerceiveFlag(true);
							continue;
						}
					}
					int k;
					for (k = 0; k < EnemyInfo::Enemy_Num; k++) {
						if (j == k)continue;
						if (!_enemy[k]->GetLiveFlag() || _enemy[k]->GetDethDelayFlag())continue;
						if (_enemy[k]->GetRopeModeFlag())continue;
						if (_island[i]->GetPosX() == _enemy[k]->GetPosX() && _island[i]->GetPosY() == _enemy[k]->GetPosY())
							break;
						if (_island[i]->GetPosX() == _enemy[k]->GetNextJumpPosX() && _island[i]->GetPosY() == _enemy[k]->GetNextJumpPosY())
							break;
					}
					if (k != EnemyInfo::Enemy_Num)continue;
					v_dx = x;
					v_dy = y;
					v_x = _island[i]->GetPosX();
					v_y = _island[i]->GetPosY();
					v_n = i;
				}
			}
		}
		_enemy[j]->_onthThinkFlag = true;
		if (!distanceFlag) {
			//_enemy[j]->SetPerceiveFlag(true);
			//v_posX[j] = v_x;
			//v_posY[j] = v_y;
			//if (v_n != -1)
			//	v_islandNumber[j] = v_n;
			_enemy[j]->SetNextJumpInfo(v_x, v_y, v_n);
		}
		if (_enemy[j]->_dis_number != ENEMYTYPE_SLIME)continue;
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
		if (_enemy[i]->GetJumpMoveFlag() && !_enemy[i]->_atackModeFlag && !_enemy[i]->GetJumpNowFlag()) {
			//int j;
			//for (j = 0; j < EnemyInfo::Enemy_Num; j++) {
			//	if (_enemy[i]->GetNextJumpPosX() == _enemy[j]->GetJumpPosX() && _enemy[i]->GetNextJumpPosY() == _enemy[j]->GetJumpPosY())
			//		break;
			//}
			//if (j != EnemyInfo::Enemy_Num)
			//	continue;

			//if (_enemy[i]->_dis_number == ENEMYTYPE_MONKEY && i != 0) {
			//	int k;
			//	for (k = 0; k < IslandInfo::Island_Num; k++) {
			//		if (_rope.GetConnectFlag(i, k) >= 1)break;
			//	}
			//	if (k != IslandInfo::Island_Num) { // ISLAND_NUMまで来なければつながっている
			//		//_enemy[j]->SetPerceiveFlag(true);
			//		continue;
			//	}
			//}

			if (_island[_enemy[i]->GetNextJumpIslandNumber()]->StateCheck_FIRE())
				continue;
			_enemy[i]->JumpStart(_enemy[i]->GetNextJumpPosX(), _enemy[i]->GetNextJumpPosY());
			//_enemy[i]->JumpMove(v_posX[i], v_posY[i]);
			_enemy[i]->OffJumpMoveFlag();
			_enemy[i]->SetLastTouchIslandNumber(num_e[i]);
		}
		//if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && _enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
		//	_enemy[i]->Attack();
		//	_player.Damage();
		//	_enemy[i]->Deth();
		//}
		if (_enemy[i]->GetPosX() <= IslandInfo::Base_Island_PosX + 2 && _enemy[i]->GetPosX() >= IslandInfo::Base_Island_PosX - 2
			&& _enemy[i]->GetPosY() <= IslandInfo::Base_Island_PosY + 2 && _enemy[i]->GetPosY() >= IslandInfo::Base_Island_PosY - 2) {
			_enemy[i]->Attack();
			_player.Damage();
			_enemy[i]->Deth();
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (_enemy[i]->_dis_number != ENEMYTYPE_DEMON)continue;
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
			if (j != IslandInfo::Island_Num) break; // 島が燃えていなければ
			int num = 3;
			while (_killCount >= num) {
				_killCount -= num;
				_totalKillCount += num;
				_rope.AddMaxLife();
				_ropeLifeUpEffect.WaitingFlagOf();
			}
			_totalKillCount += _killCount;
			_killCount = 0;
			int ropeNum = 0;
			for (j = 0; j < IslandInfo::Island_Num; j++) {
				for (int k = 0; k < IslandInfo::Island_Num; k++) {
					if (_rope.GetConnectFlag(j, k) == 1 || _rope.GetConnectFlag(j, k) == 3)ropeNum++;
				}
			}
			_rope.AllRecovery(ropeNum);

		}
	}

	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		_island[i]->Update();
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i]->Update();
		if (_killCountUI[i]->GetActiveFlag())
			_killCountUI[i]->Update();
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i]->Update();
	}
	_rope.Update();
	if (_ropeLifeUpEffect.GetActiveFlag())
		_ropeLifeUpEffect.Update();
	_thunderChargeUI.Update();
	Draw();

	if (CheckHitKey(KEY_INPUT_R)) {
		Init();
		StopSoundMem(_sh_gameplay);
	}
	if (!_player.GetLive()) {
		_sceneState = RESULT;
	}
}

void GameController::Result()
{
	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		StopSoundMem(_sh_gameplay);
		PlaySoundMem(_sh_result, DX_PLAYTYPE_BACK);
	}
	if (_mouseCount_Left == -1) {
		PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
		_sceneState = TITLE;
		Init();
	}
	DrawString(300, 300, "result", GetColor(255, 255, 255));
	DrawFormatString(300, 350, GetColor(255, 255, 255), "到達WAVE : %d", _wave);
	DrawString(300, 400, "OnClick", GetColor(255, 255, 255));
}

void GameController::Draw()
{
	DrawGraph(0, 0, _gh_background, FALSE);
	DrawExtendGraph(_cloud_posX, _cloud_posY, _cloud_posX + WindowInfo::Screen_Width, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawExtendGraph(_cloud_posX - WindowInfo::Screen_Width, _cloud_posY, _cloud_posX, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawGraph(0, 0, _gh_background2, TRUE);
	MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_UIbar, 0.8f);
	int count;
	for (count = 0; count < IslandInfo::Island_Num; count++) {
		int j;
		for (j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(count, j) != 0)break;
		}
		if (j != IslandInfo::Island_Num)break;
	}
	if (count == IslandInfo::Island_Num && _nowIsland != 0) {
		_UIstartCount++;
	}
	else {
		_UIstartCount = 0;
	}
	if (_UIstartCount > 60)
		MyDrawTurn::Instance().SetDrawItem(IslandInfo::Base_Island_PosX + 100 + cos(_time.GetGameTime() / 6.) * 3, IslandInfo::Base_Island_PosY + 20, _gh_UIStart, 0.8f);
	_thunderChargeUI.Draw();
	//DrawGraph(_cloud_posX, _cloud_posY, _gh_cloud, TRUE);
	//DrawGraph(_cloud_posX - _cloud_width, _cloud_posY, _gh_cloud, TRUE);
	//DrawFormatString(10, 610, GetColor(0, 0, 0), "hp : %d", _player.GetHP());
	if (_mouseCount_Left > 1) {
		int i;
		for (i = 0; i < IslandInfo::Island_Num; i++) {
			if (_rope.GetConnectFlag(_nowIsland, i) != 0)break;
		}
		if (i != IslandInfo::Island_Num && _rope.GetRopeLife() > 0) {
			MyDrawTurn::Instance().SetDrawBrightItem(_island[_nowIsland]->GetPosX(), _island[_nowIsland]->GetPosY(), 0, 0.5, 100, 255, 100, BLENDMODE_NOBLEND, 0, DRAWTYPE_DRAWLINE, 0, _mousePosX_Left, _mousePosY_Left);
		}
	}
	for (int i = 1; i < PlayerInfo::Player_HP; i++) {
		if (i < _player.GetHP()) {
			MyDrawTurn::Instance().SetDrawItem(IslandInfo::Base_Island_PosX - _hp_width / 2, IslandInfo::Base_Island_PosY - _hp_height / 2 + 50, _gh_hp[i - 1], 0.81f, DRAWTYPE_DRAWGRAPH, 0, 0, BLENDMODE_ALPHA, 200);
			continue;
		}
		break;
	}
	//if (!_fireReloadFlag) {
	//	DrawFormatString(10, 740, GetColor(0, 0, 0), "撃てる");
	//}
	//DrawFormatString(10, 550, GetColor(0, 0, 0), "KILL : %d", _killCount);
	//DrawFormatString(10, 720, GetColor(0, 0, 0), "発射可能まで : %d", FIRE_RELOAD_NUM - _fireReloadCount);
	MyDrawTurn::Instance().SetDrawItem(42, 670, _gh_thunderUI[_animPos_thunderUI], 0.81f);
	//DrawFormatString(10, 570, GetColor(0, 0, 0), "WAVE : %d", _wave);
	MyDrawTurn::Instance().SetDrawItem(10, 10, _gh_wave, 0.8f);
	_drawNumber.Draw(180, 10, _wave, SETDRAWNUM_WAVE);
	int ropeLife = 0;
	for (int i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		if (ropeLife < _rope.GetRopeLife()) {
			MyDrawTurn::Instance().SetDrawItem(240 + (40 * i) - 50, 766 - 50, _gh_tuta_life_active, 0.81f);
		}
		//else{
		else if(ropeLife < _rope.GetMaxRopeLife()){
			MyDrawTurn::Instance().SetDrawItem(240 + (40 * i) - 50, 766 - 50, _gh_tuta_life_inactive, 0.81f);
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
					_animPos_tuta[i][j] = 0;
				}
				_rope._moveCount[i][j]++;
				if (_rope._moveCount[i][j] % 2 == 0) {
					_animPos_tuta[i][j]++;
				}
				auto x = _island[j]->GetPosX() - _island[i]->GetPosX();
				auto y = _island[j]->GetPosY() - _island[i]->GetPosY();
				auto angle = atan2(y, x);
				double exRate = 1;
				auto xy = sqrt(abs(x * x + y * y));
				//if (abs(x + y) >= 100) {
				//	exRate = 1.2;
				//}
				exRate = xy / 100;
				//_rope._posX[i][j] += cos(angle) * 5;
				//_rope._posY[i][j] += sin(angle) * 5;
				//_rope._posX[i][j] = x / 2;
				//_rope._posY[i][j] = y / 2;
				//auto dx = _rope._posX[i][j] - _island[i]->GetPosX();
				//auto dy = _rope._posY[i][j] - _island[i]->GetPosY();
				//if (abs(_island[j]->GetPosX() - _rope._posX[i][j]) <= 3 && abs(_island[j]->GetPosY() - _rope._posY[i][j]) <= 3) {
				//	_rope._posX[i][j] = _island[j]->GetPosX();
				//	_rope._posY[i][j] = _island[j]->GetPosY();
				//	_rope.ConnectFinished(i, j);
				//}
				//if (abs(dx) > abs(x) || abs(dy) > abs(y)) {
				//	_rope._posX[i][j] = _island[j]->GetPosX();
				//	_rope._posY[i][j] = _island[j]->GetPosY();
				//	_rope.ConnectFinished(i, j);
				//}
				//auto tmdistance = (_tuta_middle_height / 2.0) + (_tuta_top_height / 2.0);
				//auto mmdistance = (_tuta_middle_height / 2.0) + (_tuta_middle_height / 2.0);
				//auto mx = (int)_rope._posX[i][j] - (int)(tmdistance * cos(angle));
				//auto my = (int)_rope._posY[i][j] - (int)(tmdistance * sin(angle));

				float priority = 0.3f;
				//if (_island[i]->GetWidth() / 2 > abs(_rope._posX[i][j] - _island[i]->GetPosX())
				//	&& _island[i]->GetHeight() / 2 > abs(_rope._posY[i][j] - _island[i]->GetPosY()))
				//	priority = 0.19f;
				if (_rope.GetFireFlag(i, j) == 0) {
					MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_anim[_animPos_tuta[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				if (_rope.GetFireFlag(i, j)) {
					//DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 0, 0), 3);
				}
				else {
					//MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_anim[_animPos_tuta[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
					//DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 255, 255), 3);
					//DrawRotaGraph(_island[i]->GetPosX() + x / 2, _island[i]->GetPosY() + y / 2, 1.0, angle, _gh_tuta, TRUE);
					//MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + (x / 2), _rope._posY[i][j] + (y / 2), _gh_tuta_top, 0.3f, DRAWTYPE_DRAWROTAGRAPH, angle);
					//float priority = 0.3f;
					//if (_island[i]->GetWidth() / 2 > abs(_rope._posX[i][j] - _island[i]->GetPosX())
					//	&& _island[i]->GetHeight() / 2 > abs(_rope._posY[i][j] - _island[i]->GetPosY()))
					//	priority = 0.19f;
					//MyDrawTurn::Instance().SetDrawItem((int)_rope._posX[i][j], (int)_rope._posY[i][j], _gh_tuta_top, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//priority = 0.3f;
					//if (dx >= abs((int)_rope._posX[i][j] - mx) || dy >= abs((int)_rope._posY[i][j] - my)) {
					//	if (_island[i]->GetWidth() / 2 > abs(mx - _island[i]->GetPosX())
					//		&& _island[i]->GetHeight() / 2 > abs(my - _island[i]->GetPosY()))
					//		priority = 0.19f;
					//	MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//	while (abs(mx - _island[i]->GetPosX()) >= abs(mmdistance * cos(angle)) && abs(my - _island[i]->GetPosY()) >= abs(mmdistance * sin(angle))) {
					//		priority = 0.3f;
					//		mx -= (int)mmdistance * cos(angle);
					//		my -= (int)mmdistance * sin(angle);
					//		if (_island[i]->GetWidth() / 2 > abs(mx - _island[i]->GetPosX())
					//			&& _island[i]->GetHeight() / 2 > abs(my - _island[i]->GetPosY()))
					//			priority = 0.19f;
					//		MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//	}
					//}
				}
				if (_animPos_tuta[i][j] >= 9) {
					_rope.ConnectFinished(i, j);
				}
			}
			if (_rope.GetConnectFlag(i, j) == 3) {
				_rope._moveCount[i][j] = 0;
				auto x = _island[j]->GetPosX() - _island[i]->GetPosX();
				auto y = _island[j]->GetPosY() - _island[i]->GetPosY();
				auto angle = atan2(y, x);
				double exRate = 1;
				auto xy = sqrt(abs(x * x + y * y));
				//if (abs(x + y) >= 100) {
				//	exRate = 1.2;
				//}
				exRate = xy / 100;
				//auto tmdistance = (_tuta_middle_height / 2.0) + (_tuta_top_height / 2.0);
				//auto mmdistance = (_tuta_middle_height / 2.0) + (_tuta_middle_height / 2.0);
				//auto mx = (int)_rope._posX[i][j] - (int)(tmdistance * cos(angle));
				//auto my = (int)_rope._posY[i][j] - (int)(tmdistance * sin(angle));

				float priority = 0.3f;
				//if (_island[i]->GetWidth() * 3 / 7 > abs(_rope._posX[i][j] - _island[i]->GetPosX())
				//	&& _island[i]->GetHeight() * 3 / 7 > abs(_rope._posY[i][j] - _island[i]->GetPosY()))
				//	priority = 0.19f;
				if (_rope.GetFireStartFlag(i, j) == 1) {
					_animCount_tuta_fire1[i][j]++;
					if (_animCount_tuta_fire1[i][j] % 2 == 0)_animPos_tuta_fire1[i][j]++;
					if (_animCount_tuta_fire1[i][j] <= 2)_animPos_tuta_fire1[i][j] = 0;
					MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_fire1_anim[_animPos_tuta_fire1[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				if (_rope.GetFireStartFlag(i, j) == 2) {
					_animCount_tuta_fire2[i][j]++;
					if (_animCount_tuta_fire2[i][j] % 2 == 0)_animPos_tuta_fire2[i][j]++;
					if (_animCount_tuta_fire2[i][j] <= 2)_animPos_tuta_fire2[i][j] = 0;
					MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_fire2_anim[_animPos_tuta_fire2[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				if (_rope.GetFireStartFlag(i, j) == 0) {
					_animCount_tuta_fire1[i][j] = 0;
					_animCount_tuta_fire2[i][j] = 0;
					_animPos_tuta_fire1[i][j] = 0;
					_animPos_tuta_fire2[i][j] = 0;
				}
				if (_rope.GetFireFlag(i, j) == 2) {
					//DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 0, 0), 3);
					MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_fire1_anim[5], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
					//MyDrawTurn::Instance().SetDrawItem((int)_rope._posX[i][j], (int)_rope._posY[i][j], _gh_tuta_fire_top, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//priority = 0.3f;
					//if (abs((int)_rope._posX[i][j] - _island[i]->GetPosX()) >= abs((int)_rope._posX[i][j] - mx) || abs((int)_rope._posY[i][j] - _island[i]->GetPosY()) >= abs((int)_rope._posY[i][j] - my)) {
					//	if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
					//		&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
					//		priority = 0.19f;
					//	MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_fire_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//	while (abs(mx - _island[i]->GetPosX()) >= abs(mmdistance * cos(angle)) && abs(my - _island[i]->GetPosY()) >= abs(mmdistance * sin(angle))) {
					//		priority = 0.3f;
					//		mx -= (int)mmdistance * cos(angle);
					//		my -= (int)mmdistance * sin(angle);
					//		if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
					//			&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
					//			priority = 0.19f;
					//		MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_fire_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//	}
					//}
				}
				else if (_rope.GetFireFlag(i, j) == 1) {
					MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_fire2_anim[5], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				else if(_rope.GetFireStartFlag(i, j) == 0) {
					DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 255, 255), 3);
					//DrawRotaGraph(_island[i]->GetPosX() + x / 2, _island[i]->GetPosY() + y / 2, 1.0, angle, _gh_tuta, TRUE);
					//MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + (x / 2), _rope._posY[i][j] + (y / 2), _gh_tuta_top, 0.3f, DRAWTYPE_DRAWROTAGRAPH, angle);
			
					//MyDrawTurn::Instance().SetDrawItem((int)_rope._posX[i][j], (int)_rope._posY[i][j], _gh_tuta_top, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//priority = 0.3f;
					//if (abs((int)_rope._posX[i][j] - _island[i]->GetPosX()) >= abs((int)_rope._posX[i][j] - mx) || abs((int)_rope._posY[i][j] - _island[i]->GetPosY()) >= abs((int)_rope._posY[i][j] - my)) {
					//	if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
					//		&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
					//		priority = 0.19f;
					//	MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//	while (abs(mx - _island[i]->GetPosX()) >= abs(mmdistance * cos(angle)) && abs(my - _island[i]->GetPosY()) >= abs(mmdistance * sin(angle))) {
					//		priority = 0.3f;
					//		mx -= (int)mmdistance * cos(angle);
					//		my -= (int)mmdistance * sin(angle);
					//		if (_island[i]->GetWidth() * 3 / 7 > abs(mx - _island[i]->GetPosX())
					//			&& _island[i]->GetHeight() * 3 / 7 > abs(my - _island[i]->GetPosY()))
					//			priority = 0.19f;
					//		MyDrawTurn::Instance().SetDrawItem(mx, my, _gh_tuta_middle, priority, DRAWTYPE_DRAWROTAGRAPH, angle + 90.0 * (M_PI / 180.0));
					//	}
					//}
					MyDrawTurn::Instance().SetDrawItem(_rope._posX[i][j] + x / 2, _rope._posY[i][j] + y / 2, _gh_tuta_anim[_animPos_tuta[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
			}
			DrawFormatString(_island[i]->GetPosX(), _island[i]->GetPosY(), GetColor(0, 0, 0), "%d", i);
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		_enemy[i]->Draw();
		if (_killCountUI[i]->GetActiveFlag())
			_killCountUI[i]->Draw();
	}
	for (int i = 0; i < BulletInfo::Bullet_Num; i++) {
		_bullet[i]->Draw();
	}
	_player.Draw();
	if (_ropeLifeUpEffect.GetActiveFlag())
		_ropeLifeUpEffect.Draw();
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
	OnMouseButtonLeft();
	OnMouseButtonRight();
	OnSpaceButton();
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
	int maximum = 3;
	//if (_enemySpawnCount == 0)maximum = 1;
	switch (_enemySpawnCount) {
	case 0:
		maximum = 1;
		break;
	case 1:
		maximum = 1;
		break;
	case 2:
		maximum = 1;
		break;
	case 6:
		maximum = 2;
		break;
	case 17:
		maximum = 1;
		break;
	case 33:
		maximum = 6;
		break;
	case 42:
		maximum = 2;
		break;
	case 50:
		maximum = 6;
		break;
	case 65:
		maximum = 6;
		break;
	case 77:
		maximum = 6;
		break;
	case 110:
		maximum = 6;
		break;
	case 119:
		maximum = 6;
		break;
	case 128:
		maximum = 6;
		break;
	case 140:
		maximum = 6;
		break;
	case 152:
		maximum = 6;
		break;
	default:
		maximum = 3;
		break;
	}
	int direction = 100;
	while (counter < maximum) {
		if (_remainingEnemyCount <= 0)break;
		_remainingEnemyCount--;
		if (counter > 2 && counter % 3 == 0) {
			int nextRandam = GetRand(3 - 1);
			while (nextRandam == random) {
				nextRandam = GetRand(3 - 1);
			}
			random = nextRandam;
		}
		int i;
		for (i = 0; i < EnemyInfo::Enemy_Num; i++) {
			if (!_enemy[i]->GetLiveFlag())break;;
		}
		int x, y;
		switch (random) {
		case 0:
			if (counter % 3 == 0)x = -40, y = 40;
			if (counter % 3 == 1)x = 40, y = 0;
			if (counter % 3 == 2)x = -20, y = -30;
			_enemy[i]->SetFirstPosition(IslandInfo::Base_Island_PosX - 400 + x, IslandInfo::Base_Island_PosY - 510 + y);
			_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX - 400 - 200 + x, IslandInfo::Base_Island_PosY - 510 + y, _enemySpawnNumber[_enemySpawnCount]);
			_enemySpawnCount++;
			break;
		case 1:
			if (counter % 3 == 0)x = -60, y = 0;
			if (counter % 3 == 1)x = 60, y = 0;
			if (counter % 3 == 2)x = 0, y = -10;
			_enemy[i]->SetFirstPosition(IslandInfo::Base_Island_PosX + x, IslandInfo::Base_Island_PosY - 600 + y);
			_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + x, IslandInfo::Base_Island_PosY - 600 - 100 + y, _enemySpawnNumber[_enemySpawnCount]);
			_enemySpawnCount++;
			break;
		case 2:
			if (counter % 3 == 0)x = 40, y = 40;
			if (counter % 3 == 1)x = -40, y = 0;
			if (counter % 3 == 2)x = 20, y = -30;
			_enemy[i]->SetFirstPosition(IslandInfo::Base_Island_PosX + 400 + x, IslandInfo::Base_Island_PosY - 510 + y);
			_enemy[i]->Instantiate(IslandInfo::Base_Island_PosX + 400 + 200 + x, IslandInfo::Base_Island_PosY - 510 + y, _enemySpawnNumber[_enemySpawnCount]);
			_enemySpawnCount++;
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

void GameController::EnemySpawnNumberInit()
{
	//_enemySpawnNumber[1] = ENEMYTYPE_DEMON;
	//_enemySpawnNumber[2] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[0] = ENEMYTYPE_SLIME; //1
	_enemySpawnNumber[1] = ENEMYTYPE_SLIME; //1
	_enemySpawnNumber[2] = ENEMYTYPE_SLIME; //1

	_enemySpawnNumber[3] = ENEMYTYPE_SLIME; 
	_enemySpawnNumber[4] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[5] = ENEMYTYPE_SLIME;  
	_enemySpawnNumber[6] = ENEMYTYPE_DEMON; //2
	_enemySpawnNumber[7] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[8] = ENEMYTYPE_SLIME; 
	_enemySpawnNumber[9] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[10] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[11] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[12] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[13] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[14] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[15] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[16] = ENEMYTYPE_SLIME;

	_enemySpawnNumber[17] = ENEMYTYPE_MONKEY; // 1
	_enemySpawnNumber[18] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[19] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[20] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[21] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[22] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[23] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[24] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[25] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[26] = ENEMYTYPE_SLIME;

	_enemySpawnNumber[27] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[28] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[29] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[30] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[31] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[32] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[33] = ENEMYTYPE_DEMON; //6
	_enemySpawnNumber[34] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[35] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[36] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[37] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[38] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[39] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[40] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[41] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[42] = ENEMYTYPE_MONKEY; //2
	_enemySpawnNumber[43] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[44] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[45] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[46] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[47] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[48] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[49] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[50] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[51] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[52] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[53] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[54] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[55] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[56] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[57] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[58] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[59] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[60] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[61] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[62] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[63] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[64] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[65] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[66] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[67] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[68] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[69] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[70] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[71] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[72] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[73] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[74] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[75] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[76] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[77] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[78] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[79] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[80] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[81] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[82] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[83] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[84] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[85] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[86] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[87] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[88] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[89] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[90] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[91] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[92] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[93] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[94] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[95] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[96] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[97] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[98] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[99] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[100] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[101] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[102] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[103] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[104] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[105] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[106] = ENEMYTYPE_SLIME;

	_enemySpawnNumber[107] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[108] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[109] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[110] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[111] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[112] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[113] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[114] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[115] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[116] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[117] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[118] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[119] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[120] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[121] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[122] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[123] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[124] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[125] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[126] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[127] = ENEMYTYPE_DEMON;

	_enemySpawnNumber[128] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[129] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[130] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[131] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[132] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[133] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[134] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[135] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[136] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[137] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[138] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[139] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[140] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[141] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[142] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[143] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[144] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[145] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[146] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[147] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[148] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[149] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[150] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[151] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[152] = ENEMYTYPE_MONKEY; //6
	_enemySpawnNumber[153] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[154] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[155] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[156] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[157] = ENEMYTYPE_SLIME;
}
