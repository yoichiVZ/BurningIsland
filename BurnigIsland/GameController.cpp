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
	LoadDivGraph("Resource\\Image\\yugudorasiru3.png", 14, 5, 3, 50, 60, _gh_crystal);
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
	_gh_black = LoadGraph("Resource\\Image\\Anten.png");
	_gh_next = LoadGraph("Resource\\Image\\NEXT.png");
	_gh_gameover = LoadGraph("Resource\\Image\\GAMEOVER.png");
	_gh_result = LoadGraph("Resource\\Image\\Result.png");
	_gh_resultWave = LoadGraph("Resource\\Image\\ResultWAVE.png");
	_gh_white = LoadGraph("Resource\\Image\\hikari.png");
	_gh_gameclear = LoadGraph("Resource\\Image\\VICTORY.png");
	_gh_thanks = LoadGraph("Resource\\Image\\THANKS.png");

	_sh_title = LoadSoundMem("Resource\\Sound\\title.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_title);
	_sh_tutorial = LoadSoundMem("Resource\\Sound\\tutorial.mp3");
	ChangeVolumeSoundMem(255 * 25 / 100, _sh_tutorial);
	_sh_gameplay = LoadSoundMem("Resource\\Sound\\gameplay.mp3");
	ChangeVolumeSoundMem(255 * 25 / 100, _sh_gameplay);
	_sh_gameClear = LoadSoundMem("Resource\\Sound\\gameClear.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_gameClear);
	_sh_gameOver = LoadSoundMem("Resource\\Sound\\gameOver.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_gameOver);
	_sh_thunder = LoadSoundMem("Resource\\Sound\\thunder.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_thunder);
	_sh_thunderCharge = LoadSoundMem("Resource\\Sound\\thunderCharge.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_thunderCharge);
	_sh_click = LoadSoundMem("Resource\\Sound\\Click.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_click);
	_sh_tuta_imposible = LoadSoundMem("Resource\\Sound\\tuta_imposible.wav");
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
	for (i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		//_circleEfect[i] = new CircleEfect();
		_ropeLifeDownEffect[i] = new RopeLifeDownEfect();
	}
	for (i = 0; i < 5; i++) {
		_ropeLifeUpEffect[i] = new RopeLifeUpEffect();
	}
	for (i = 0; i < SHIELDBREAKEFFECT_NUM; i++) {
		_shieldBreakEffect[i] = new ShieldBreakEffect();
	}
	for (i = 0; i < 4; i++) {
		_island_tutorial[i] = new Island();
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
	for (i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		//delete _circleEfect[i];
		delete _ropeLifeDownEffect[i];
	}
	for (i = 0; i < 5; i++) {
		delete _ropeLifeUpEffect[i];
	}
	for (i = 0; i < SHIELDBREAKEFFECT_NUM; i++) {
		delete _shieldBreakEffect[i];
	}
	for (i = 0; i < 4; i++) {
		delete _island_tutorial[i];
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
	for (int i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		_ropeLifeDownEffect[i]->Init();
	}
	for (int i = 0; i < 5; i++) {
		_ropeLifeUpEffect[i]->Init();
	}
	for (int i = 0; i < SHIELDBREAKEFFECT_NUM; i++) {
		_shieldBreakEffect[i]->Init();
	}
	_player.Init();
	_rope.Init();
	_time.Init();
	_thunderChargeUI.Init();
	_waveUpEffect.Init();

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
	_wavePreparationCount = 0;
	_remainingEnemyCount = 0;
	_UIstartCount = 0;
	_tutorialCount = 0;
	_gameOverFlag = 0;
	_gameClearFlag = 0;

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
	//_nowIsland = 0;
	_now_player_num = 0;
	_touchIslandFlag = 0;

	_enemySpawnCount = 0;

	_white_paramVol = 0;
	_black_paramVol = 0;
	_nextCount = 0;
	_nextPosCount = 0;
	_nextVecCount = 0;
	_gameoverAlphaCount = 0;
	_gameclearAlphaCount = 0;
	_gameclear_thanksAlphaCount = 0;

	_animPos_crystal = 0;
	_animCount_crystal = 0;

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
		StopSoundMem(_sh_gameClear);
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
		557 < mousePosY && 557 + tutorialHeight > mousePosY) {
		MyDrawTurn::Instance().SetDrawItem(480 + tutorialWidth / 2, 557 + tutorialHeight / 2, _gh_title_tutorial, 0.5f, DRAWTYPE_DRAWROTAGRAPH, 1.2);
		if (_mouseCount_Left == -1) {
			_onth_flag[_sceneState] = 0;
			PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
			_sceneState = TUTORIAL;
		}
	}
	else {
		MyDrawTurn::Instance().SetDrawItem(480 + tutorialWidth / 2, 557 + tutorialHeight / 2, _gh_title_tutorial, 0.5f, DRAWTYPE_DRAWROTAGRAPH, 1);
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
	_nextPosCount++;

	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		_tutorialCount = 0;
		_nextVecCount = 0;
		StopSoundMem(_sh_title);
		PlaySoundMem(_sh_tutorial, DX_PLAYTYPE_LOOP);

		for (int i = 0; i < 4; i++) {
			_island_tutorial[i]->Init();
			for (int j = 0; j < 4; j++) {
				_animPos_tuta_tutorial[i][j] = 0;
				_animPos_tuta_fire1_tutorial[i][j] = 0;
				_animPos_tuta_fire2_tutorial[i][j] = 0;
				_animCount_tuta_fire1_tutorial[i][j] = 0;
				_animCount_tuta_fire2_tutorial[i][j] = 0;
			}
		}
		_rope_tutorial.Init();
		_tutorialFlag = 0;
		_island_tutorial[0]->SetPosition(230, 300);
		_island_tutorial[1]->SetPosition(230, 200);
		_island_tutorial[2]->SetPosition(600, 270);
		_island_tutorial[3]->SetPosition(700, 270);

		_animPos_tuta_tutorial[2][3] = 9;
		_rope_tutorial._posX[2][3] = _island_tutorial[2]->GetPosX();
		_rope_tutorial._posY[2][3] = _island_tutorial[2]->GetPosY();

		_rope_tutorial.ConnectFinished(2, 3);

		_now_player_num = 0;
	}
	if (_mouseCount_Left == -1) {
		if (_tutorialCount == 1) {
			if (_tutorialFlag >= 3)
				_tutorialCount++;
		}
		else
			_tutorialCount++;
	}
	if (_tutorialCount >= 4) {
		_onth_flag[_sceneState] = 0;
		PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
		_sceneState = TITLE;
		_fireReloadCount = 0;
		_fireReloadFlag = false;
		//Init();
	}
	else {
		MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_title_background, 0.01f);
		MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_cloud, 0.02f);
		MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_tutorial[_tutorialCount], 0.03f);
		if (_tutorialCount == 1) {
			if (_tutorialFlag >= 3)
				MyDrawTurn::Instance().SetDrawItem(WindowInfo::Screen_Width - 100, WindowInfo::Screen_Height - 100 + sin(_nextPosCount / 6) * 3, _gh_next, 0.51f);
		}
		else
			MyDrawTurn::Instance().SetDrawItem(WindowInfo::Screen_Width - 100, WindowInfo::Screen_Height - 100 + sin(_nextPosCount / 6) * 3, _gh_next, 0.51f);
	}

	if (_tutorialCount != 1)return;

	for (int i = 0; i < 4; i++) {
		if (_island_tutorial[i]->PlayerStayCheck(_player.GetPosX(), _player.GetPosY())) {
			_now_player_num = i;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (i == _now_player_num)continue;
		if (_island_tutorial[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
			//if (_island[_now_player_num]->StateCheck_BURN())continue;
			if (_touchIslandFlag == 1) { // 左クリックしてる間
				if (_island_tutorial[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island_tutorial[i]->GetPosX() + IslandInfo::Island_Rotation &&
					_island_tutorial[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island_tutorial[i]->GetPosY() + IslandInfo::Island_Rotation &&
					_rope_tutorial.GetConnectFlag(_now_player_num, i) == 0)
				{
					if (_island_tutorial[i]->StateCheck_BURN()) {
						_island_tutorial[i]->Revival();
					}
					_rope_tutorial.Connect(_now_player_num, i);
					if (_tutorialFlag == 1)_tutorialFlag++;
				}
			}
		}
	}
	if (_mouseCount_Left >= 1) { // 左クリックしてる間
		for (int i = 0; i < 4; i++) {
			if (_island_tutorial[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island_tutorial[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island_tutorial[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island_tutorial[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				_player.Move(_island_tutorial[i]->GetPosX(), _island_tutorial[i]->GetPosY());
				_touchIslandFlag = 1;
				_island_tutorial[i]->Revival();
				if (_tutorialFlag == 0)_tutorialFlag++;
				//_nowIsland = i;
			}
		}
	}
	else {
		_touchIslandFlag = 0;
	}

	for (int i = 0; i < 4; i++) {
		if (_thunder_count[i] > 0) {
			_thunder_count[i]--;
		}
	}
	if (_fireReloadFlag) {
		_fireReloadCount++;
	}
	if (_fireReloadCount > 60) {
		_fireReloadCount = 0;
		_fireReloadFlag = false;
	}
	if (_mouseCount_Right == 1 && _tutorialFlag > 1) { // 右クリックした瞬間
		for (int i = 0; i < 4; i++) {
			if (_island_tutorial[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Right && _mousePosX_Right < _island_tutorial[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island_tutorial[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Right && _mousePosY_Right < _island_tutorial[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				if (!_fireReloadFlag) {
					_island_tutorial[i]->Burning();
					_fireReloadFlag = true;
					_thunder_count[i] = 25;
					PlaySoundMem(_sh_thunder, DX_PLAYTYPE_BACK);
					_tutorialFlag++;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (_rope_tutorial.GetConnectFlag(i, j) >= 1) {
				if (_island_tutorial[i]->StateCheck_FIRE() && (_rope_tutorial.GetFireFlag(i, j) == 0 && _rope_tutorial.GetFireStartFlag(i, j) == 0)) {
					_rope_tutorial.Ignition(i, j);
				}
				if (_island_tutorial[j]->StateCheck_FIRE() && (_rope_tutorial.GetFireFlag(i, j) == 0 && _rope_tutorial.GetFireStartFlag(i, j) == 0)) {
					_rope_tutorial.Ignition(j, i);
				}
				if (_rope_tutorial.GetFireFlag(i, j) != 0 && _island_tutorial[i]->StateCheck_GRASS() && _island_tutorial[i]->GetFireStartflag() == 0) {
					_island_tutorial[i]->Ignition();
				}
				if (_rope_tutorial.GetFireFlag(i, j) != 0 && _island_tutorial[j]->StateCheck_GRASS() && _island_tutorial[j]->GetFireStartflag() == 0) {

					_island_tutorial[j]->Ignition();
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		_island_tutorial[i]->Update();
	}
	_rope_tutorial.Update();

	if (_tutorialFlag == 0) {
		MyDrawTurn::Instance().SetDrawItem(300 + cos(_nextPosCount / 6) * 3, 300, _gh_next, 0.6f,DRAWTYPE_DRAWROTAGRAPH,0.5,90 * (3.1415 / 180));
	}
	if (_tutorialFlag == 1) {
		//if (_nextPosCount % 2) 
		_nextVecCount++;
		if (_nextVecCount <= 100)
			MyDrawTurn::Instance().SetDrawItem(300, 300 - _nextVecCount, _gh_next, 0.6f, DRAWTYPE_DRAWROTAGRAPH, 0.5, 90 * (3.1415 / 180));
		else
			MyDrawTurn::Instance().SetDrawItem(300, 300 - 100, _gh_next, 0.6f, DRAWTYPE_DRAWROTAGRAPH, 0.5, 90 * (3.1415 / 180));
		if (_nextVecCount > 120)
			_nextVecCount = 0;
	}
	if (_tutorialFlag == 2) {
		MyDrawTurn::Instance().SetDrawItem(600, 240 + sin(_nextPosCount / 6) * 3, _gh_next, 0.6f, DRAWTYPE_DRAWROTAGRAPH, 0.5);
	}
	//if (_tutorialFlag == 3) {
	//	MyDrawTurn::Instance().SetDrawItem(WindowInfo::Screen_Width - 100, WindowInfo::Screen_Height - 100 + sin(_nextPosCount / 6) * 3, _gh_next, 0.51f);
	//}
	
	for (int i = 0; i < 4; i++) {
		_island_tutorial[i]->Draw();
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (_rope_tutorial.GetConnectFlag(i, j) == 1) {
				if (_rope_tutorial._moveCount[i][j] == 0) {
					_rope_tutorial._posX[i][j] = _island_tutorial[i]->GetPosX();
					_rope_tutorial._posY[i][j] = _island_tutorial[i]->GetPosY();
					_animPos_tuta_tutorial[i][j] = 0;
				}
				_rope_tutorial._moveCount[i][j]++;
				if (_rope_tutorial._moveCount[i][j] % 2 == 0) {
					_animPos_tuta_tutorial[i][j]++;
				}
				auto x = _island_tutorial[j]->GetPosX() - _island_tutorial[i]->GetPosX();
				auto y = _island_tutorial[j]->GetPosY() - _island_tutorial[i]->GetPosY();
				auto angle = atan2(y, x);
				double exRate = 1;
				auto xy = sqrt(abs(x * x + y * y));
				exRate = xy / 100;
				float priority = 0.3f;
				if (_rope_tutorial.GetFireFlag(i, j) == 0) {
					MyDrawTurn::Instance().SetDrawItem(_rope_tutorial._posX[i][j] + x / 2, _rope_tutorial._posY[i][j] + y / 2, _gh_tuta_anim[_animPos_tuta_tutorial[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				if (_animPos_tuta_tutorial[i][j] >= 9) {
					_rope_tutorial.ConnectFinished(i, j);
				}
			}
			if (_rope_tutorial.GetConnectFlag(i, j) == 3) {
				_rope_tutorial._moveCount[i][j] = 0;
				auto x = _island_tutorial[j]->GetPosX() - _island_tutorial[i]->GetPosX();
				auto y = _island_tutorial[j]->GetPosY() - _island_tutorial[i]->GetPosY();
				auto angle = atan2(y, x);
				double exRate = 1;
				auto xy = sqrt(abs(x * x + y * y));
				exRate = xy / 100;
				float priority = 0.52f;
				if (_rope_tutorial.GetFireStartFlag(i, j) == 1) {
					_animCount_tuta_fire1_tutorial[i][j]++;
					if (_animCount_tuta_fire1_tutorial[i][j] % 2 == 0)_animPos_tuta_fire1_tutorial[i][j]++;
					if (_animCount_tuta_fire1_tutorial[i][j] <= 2)_animPos_tuta_fire1_tutorial[i][j] = 0;
					MyDrawTurn::Instance().SetDrawItem(_rope_tutorial._posX[i][j] + x / 2, _rope_tutorial._posY[i][j] + y / 2, _gh_tuta_fire1_anim[_animPos_tuta_fire1_tutorial[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				if (_rope_tutorial.GetFireStartFlag(i, j) == 2) {
					_animCount_tuta_fire2_tutorial[i][j]++;
					if (_animCount_tuta_fire2_tutorial[i][j] % 2 == 0)_animPos_tuta_fire2_tutorial[i][j]++;
					if (_animCount_tuta_fire2_tutorial[i][j] <= 2)_animPos_tuta_fire2_tutorial[i][j] = 0;
					MyDrawTurn::Instance().SetDrawItem(_rope_tutorial._posX[i][j] + x / 2, _rope_tutorial._posY[i][j] + y / 2, _gh_tuta_fire2_anim[_animPos_tuta_fire2_tutorial[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				if (_rope_tutorial.GetFireStartFlag(i, j) == 0) {
					_animCount_tuta_fire1_tutorial[i][j] = 0;
					_animCount_tuta_fire2_tutorial[i][j] = 0;
					_animPos_tuta_fire1_tutorial[i][j] = 0;
					_animPos_tuta_fire2_tutorial[i][j] = 0;
				}
				if (_rope_tutorial.GetFireFlag(i, j) == 2) {
					MyDrawTurn::Instance().SetDrawItem(_rope_tutorial._posX[i][j] + x / 2, _rope_tutorial._posY[i][j] + y / 2, _gh_tuta_fire1_anim[5], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				else if (_rope_tutorial.GetFireFlag(i, j) == 1) {
					MyDrawTurn::Instance().SetDrawItem(_rope_tutorial._posX[i][j] + x / 2, _rope_tutorial._posY[i][j] + y / 2, _gh_tuta_fire2_anim[5], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
				else if (_rope_tutorial.GetFireStartFlag(i, j) == 0) {
					//DrawLine(_island[i]->GetPosX(), _island[i]->GetPosY(), _island[j]->GetPosX(), _island[j]->GetPosY(), GetColor(255, 255, 255), 3);
					MyDrawTurn::Instance().SetDrawItem(_rope_tutorial._posX[i][j] + x / 2, _rope_tutorial._posY[i][j] + y / 2, _gh_tuta_anim[_animPos_tuta_tutorial[i][j]], priority, DRAWTYPE_DRAWROTAGRAPH, exRate, angle + 90.0 * (M_PI / 180.0));
				}
			}
		}
	}
	if (_touchIslandFlag == 1) {
		
		MyDrawTurn::Instance().SetDrawBrightItem(_island_tutorial[_now_player_num]->GetPosX(), _island_tutorial[_now_player_num]->GetPosY(), 0, 0.7, 100, 255, 100, BLENDMODE_NOBLEND, 0, DRAWTYPE_DRAWLINE, 0, _mousePosX_Left, _mousePosY_Left);
		
	}
	for (int i = 0; i < 4; i++) {
		if (_thunder_count[i] > 0) {
			if (_thunder_count[i] % 5 == 0)_animPos_thunder[i]++;
			MyDrawTurn::Instance().SetDrawItem(_island_tutorial[i]->GetPosX() - _thunder_width / 2, _island_tutorial[i]->GetPosY() - _thunder_height + 10, _gh_thunder[_animPos_thunder[i]], 0.5f);
		}
		else {
			_animPos_thunder[i] = 0;
		}
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

		_player.Init();
	}
	if (_gameOverFlag == 0 && _gameClearFlag == 0) {
		Update();
	}
	if (_gameOverFlag == 1) {
		GameOverUpdate();
		GameOverDraw();
	}
	else if (_gameClearFlag == 1) {
		GameClearUpdate();
		GameClearDraw();
	}
	Draw();
}

void GameController::Result()
{
	if (_onth_flag[_sceneState] == 0) {
		_onth_flag[_sceneState]++;
		StopSoundMem(_sh_gameplay);
		PlaySoundMem(_sh_gameClear, DX_PLAYTYPE_BACK);
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

void GameController::Update()
{
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
				_remainingEnemyCount = 5;
				break;
			case 2:
				_remainingEnemyCount = 12;
				break;
			case 3:
				_remainingEnemyCount = 11;
				break;
			case 4:
				_remainingEnemyCount = 14;
				break;
			case 5:
				_remainingEnemyCount = 17;
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
				//_sceneState = RESULT;
				_gameClearFlag = 1;
				break;
			}
			_enemyResponCount += 1000;
			_wavePreparationCount = 60;
			if (_wave != 11)
				_waveUpEffect.Instantiate(_wave);
		}
	}
	if (_wavePreparationCount > 0) {
		_wavePreparationCount--;
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

	if (_enemyResponCount > levelCheck && _wavePreparationCount <= 0) {
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
	//int num_e[EnemyInfo::Enemy_Num];
	//for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
	//	num_e[i] = 0;
	//}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_island[j]->EnemyStayCheck(_enemy[i]->GetPosX(), _enemy[i]->GetPosY())) {
				//num_e[i] = j;
				_enemy[i]->_stayIsland = j;
				if (_island[j]->StateCheck_FIRE()) {
					_enemy[i]->Deth_Fire();
					//_rope.Recovery();
					_killCount++;
					_killCountUI[i]->SetActive(_enemy[i]->GetPosX(), _enemy[i]->GetPosY(), _killCount);
					int lifeCount = 0;
					for (int k = 0; k < 5; k++) {
						if (_ropeLifeUpEffect[k]->GetActiveFlag())lifeCount++;
					}
					if (_killCount % 3 == 0 && _rope.GetMaxRopeLife() + lifeCount < RopeInfo::Rope_MaxLife) {
						for (int k = 0; k < 5; k++) {
							if (!_ropeLifeUpEffect[k]->GetActiveFlag()) {
								_ropeLifeUpEffect[k]->SetEffect(_enemy[i]->GetPosX(), _enemy[i]->GetPosY(), 240 + (40 * (_rope.GetMaxRopeLife() + lifeCount)) + 8, 766 - 5);
								break;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
		if (_enemy[i]->_dis_number != ENEMYTYPE_SLIME)continue;
		if (!_enemy[i]->GetRopeModeFlag())continue;
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
			for (int k = 0; k < IslandInfo::Island_Num; k++) {
				if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
				if (_rope.GetFireFlag(j, k) >= 1) {
					//auto rdx = _island[j]->GetPosX() - _island[k]->GetPosX();
					//auto rdy = _island[j]->GetPosY() - _island[k]->GetPosY();

					//auto dx = _island[k]->GetPosX() + rdx / 2 - _enemy[i]->GetPosX();
					//auto dy = _island[k]->GetPosY() + rdy / 2 - _enemy[i]->GetPosY();

					//if (dx < _enemy[i]->GetSuraimuWidth() / 2 && dy < _enemy[i]->GetSuraimuHeight() / 2) {
					if(_enemy[i]->_stayIsland == j || _enemy[i]->_stayIsland == k){
						_enemy[i]->Deth_Fire();
						//_rope.Recovery();
						_killCount++;
						_killCountUI[i]->SetActive(_enemy[i]->GetPosX(), _enemy[i]->GetPosY(), _killCount);
						int lifeCount = 0;
						for (int k = 0; k < 5; k++) {
							if (_ropeLifeUpEffect[k]->GetActiveFlag())lifeCount++;
						}
						if (_killCount % 3 == 0 && _rope.GetMaxRopeLife() + lifeCount < RopeInfo::Rope_MaxLife) {
							for (int k = 0; k < 5; k++) {
								if (!_ropeLifeUpEffect[k]->GetActiveFlag()) {
									_ropeLifeUpEffect[k]->SetEffect(_enemy[i]->GetPosX(), _enemy[i]->GetPosY(), 240 + (40 * (_rope.GetMaxRopeLife() + lifeCount)) + 8, 766 - 5);
									break;
								}
							}
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
			//if (_mouseCount_Left == 1) { // 左クリックした瞬間
			//	if (i == 0) {
			//		if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
			//			_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30 &&
			//			_rope.GetConnectFlag(_now_player_num, i) == 0)
			//		{
			//			//if (_island[i]->StateCheck_BURN()) {
			//			//	_island[i]->Revival();
			//			//	_rope.Minus();
			//			//}
			//			if (_rope.GetRopeLife() > 0) {
			//				_rope.Connect(_now_player_num, i);
			//				_rope.Minus();
			//				continue;
			//			}
			//			else {
			//				if (CheckSoundMem(_sh_tuta_imposible) == 0)
			//					PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
			//			}
			//		}
			//	}
			//	if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
			//		_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
			//		_rope.GetConnectFlag(_now_player_num, i) == 0)
			//	{
			//		if (_rope.GetRopeLife() > 0) {
			//			if (_island[i]->StateCheck_BURN()) {
			//				_island[i]->Revival();
			//				_rope.Minus();
			//			}
			//			_rope.Connect(_now_player_num, i);
			//			_rope.Minus();
			//		}
			//		else {
			//			if (CheckSoundMem(_sh_tuta_imposible) == 0)
			//				PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
			//		}
			//	}
			//}
			//else if (_mouseCount_Left > 1) { // 左クリックしてる間
			//	if (i == 0) {
			//		if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
			//			_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30 &&
			//			_rope.GetConnectFlag(_now_player_num, i) == 0)
			//		{
			//			//if (_island[i]->StateCheck_BURN()) {
			//			//	_island[i]->Revival();
			//			//	_rope.Minus();
			//			//}
			//			if (_rope.GetRopeLife() > 0) {
			//				_rope.Connect(_now_player_num, i);
			//				_rope.Minus();
			//				continue;
			//			}
			//			else {
			//				if (CheckSoundMem(_sh_tuta_imposible) == 0)
			//					PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
			//			}
			//		}
			//	}
			//	if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
			//		_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
			//		_rope.GetConnectFlag(_now_player_num, i) == 0)
			//	{
			//		if (_rope.GetRopeLife() > 0) {
			//			if (_island[i]->StateCheck_BURN()) {
			//				_island[i]->Revival();
			//				_rope.Minus();
			//			}
			//			_rope.Connect(_now_player_num, i);
			//			_rope.Minus();
			//		}
			//		else {
			//			if (CheckSoundMem(_sh_tuta_imposible) == 0)
			//				PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
			//		}
			//	}
			//}
			if (_touchIslandFlag == 1) {
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
							for (int j = 0; j < RopeInfo::Rope_MaxLife; j++) {
								if (_ropeLifeDownEffect[j]->GetActiveFlag())continue;
								_ropeLifeDownEffect[j]->SetEffect(240 + (40 * _rope.GetRopeLife()) - 42, 766 - 1);
								break;
							}
							_rope.Minus();
							continue;
						}
						else {
							//if (CheckSoundMem(_sh_tuta_imposible) == 0)
								PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
						}
					}
				}
				if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation &&
					_rope.GetConnectFlag(_now_player_num, i) == 0)
				{
					if (_rope.GetRopeLife() > 0) {
						if (_island[i]->StateCheck_BURN() && _rope.GetRopeLife() > 1) {
							_island[i]->Revival();
							for (int j = 0; j < RopeInfo::Rope_MaxLife; j++) {
								if (_ropeLifeDownEffect[j]->GetActiveFlag())continue;
								_ropeLifeDownEffect[j]->SetEffect(240 + (40 * _rope.GetRopeLife()) - 42 + 8, 766 - 1 - 5);
								//240 + (40 * i) - 42, 766 - 55
								break;
							}
							_rope.Minus();
						}
						_rope.Connect(_now_player_num, i);
						for (int j = 0; j < RopeInfo::Rope_MaxLife; j++) {
							if (_ropeLifeDownEffect[j]->GetActiveFlag())continue;
							_ropeLifeDownEffect[j]->SetEffect(240 + (40 * _rope.GetRopeLife()) - 42 + 8, 766 - 1 - 5);
							break;
						}
						_rope.Minus();
					}
					else {
						//if (CheckSoundMem(_sh_tuta_imposible) == 0)
							PlaySoundMem(_sh_tuta_imposible, DX_PLAYTYPE_BACK);
					}
				}
			}
		}
	}
	if (_mouseCount_Left >= 1) { // 左クリックしてる間
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (i == 0) {
				if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
					_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30)
				{
					_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
					_touchIslandFlag = 1;
					//_nowIsland = i;
					break;
				}
			}
			if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
				_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
			{
				_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
				_touchIslandFlag = 1;
				//_nowIsland = i;
			}
		}
	}
	else {
		_touchIslandFlag = 0;
	}
	//if (_mouseCount_Left == 1) { // 左クリックした瞬間
	//	for (int i = 0; i < IslandInfo::Island_Num; i++) {
	//		if (i == 0) {
	//			if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
	//				_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30)
	//			{
	//				_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
	//				//_nowIsland = i;
	//				break;
	//			}
	//		}
	//		if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
	//			_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
	//		{
	//			_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
	//			//_nowIsland = i;
	//		}
	//	}
	//}
	//else if (_mouseCount_Left > 1) { // 左クリックしてる間
	//	for (int i = 0; i < IslandInfo::Island_Num; i++) {
	//		if (i == 0) {
	//			if (_island[i]->GetPosX() - IslandInfo::Base_Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Base_Island_Rotation &&
	//				_island[i]->GetPosY() - IslandInfo::Base_Island_Rotation + 10 < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Base_Island_Rotation + 30)
	//			{
	//				_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
	//				//_nowIsland = i;
	//				break;
	//			}
	//		}
	//		if (_island[i]->GetPosX() - IslandInfo::Island_Rotation < _mousePosX_Left && _mousePosX_Left < _island[i]->GetPosX() + IslandInfo::Island_Rotation &&
	//			_island[i]->GetPosY() - IslandInfo::Island_Rotation < _mousePosY_Left && _mousePosY_Left < _island[i]->GetPosY() + IslandInfo::Island_Rotation)
	//		{
	//			_player.Move(_island[i]->GetPosX(), _island[i]->GetPosY());
	//			//_nowIsland = i;
	//		}
	//	}
	//}
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
						//if (_enemy[j]->_stayIsland == i && !_enemy[j]->GetJumpNowFlag() && !_enemy[j]->GetRopeModeFlag()) {
						//if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
						if (_island[i]->EnemyStayCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY()) && !_enemy[j]->GetRopeModeFlag()) {
							_enemy[j]->Deth_Fire();
							_killCount++;
							_killCountUI[j]->SetActive(_enemy[j]->GetPosX(), _enemy[j]->GetPosY(), _killCount);
							int lifeCount = 0;
							for (int k = 0; k < 5; k++) {
								if (_ropeLifeUpEffect[k]->GetActiveFlag())lifeCount++;
							}
							if (_killCount % 3 == 0 && _rope.GetMaxRopeLife() + lifeCount < RopeInfo::Rope_MaxLife) {
								for (int k = 0; k < 5; k++) {
									if (!_ropeLifeUpEffect[k]->GetActiveFlag()) {
										_ropeLifeUpEffect[k]->SetEffect(_enemy[j]->GetPosX(), _enemy[j]->GetPosY(), 240 + (40 * (_rope.GetMaxRopeLife() + lifeCount)) + 8, 766 - 5);
										break;
									}
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
					if (i != 0)
						_island[i]->Ignition();
				}
				if (_rope.GetFireFlag(i, j) != 0 && _island[j]->StateCheck_GRASS() && _island[j]->GetFireStartflag() == 0) {
					if (j != 0)
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
		//if (!_enemy[j]->GetJumpMoveFlag())continue;
		//if (_enemy[j]->GetNextDecisionFlag() == 1)continue;

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
		bool jumpImposibleFlag = false;
		bool jumpPosibleFlag = false;
		bool vertualJumpFlag = false;
		bool rialJumpFlag = false;

		//for (int k = 0; k < IslandInfo::Island_Num; k++) {
		//	if(_island[num_e[j]]->EnemyDistanseCheck())
		//}
		for (int k = 0; k < IslandInfo::Island_Num; k++) {
			if (_island[k]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
				distanceFlag = true;
			}
		}

		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			//if (i == num_e[j])continue;
			//if (i == _enemy[j]->_stayIsland) continue;

			if (_island[i]->EnemyDistanseCheck(_enemy[j]->GetPosX(), _enemy[j]->GetPosY())) {
				//distanceFlag = true;
				if (_rope.GetConnectFlag(_enemy[j]->_stayIsland, i) >= 3 && !_enemy[j]->GetRopeModeFlag() && _enemy[j]->_dis_number == ENEMYTYPE_SLIME) {
					if (i == _enemy[j]->GetLastTouchIslandNumber())continue;
					//if (_enemy[j]->_dis_number != ENEMYTYPE_SLIME)continue;

					_enemy[j]->SetAngle(atan2(_island[i]->GetPosY() - _island[_enemy[j]->_stayIsland]->GetPosY(), _island[i]->GetPosX() - _island[_enemy[j]->_stayIsland]->GetPosX()));

					//double x1, y1, x2, y2, xy1, xy2, n_x1, n_y1, n_x2, n_y2;

					auto x1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosX() - _island[_enemy[j]->_stayIsland]->GetPosX();
					auto y1 = _island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosY() - _island[_enemy[j]->_stayIsland]->GetPosY();
					auto x2 = _island[i]->GetPosX() - _island[_enemy[j]->_stayIsland]->GetPosX();
					auto y2 = _island[i]->GetPosY() - _island[_enemy[j]->_stayIsland]->GetPosY();

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
					//if (_enemy[j]->GetNextDecisionFlag() == 1)continue;
					if (_enemy[j]->GetNextDecisionFlag() == 1 && _enemy[j]->_dis_number == ENEMYTYPE_MONKEY && i != 0) {
						int k;
						for (k = 0; k < IslandInfo::Island_Num; k++) {
							if (_rope.GetConnectFlag(_enemy[j]->GetNextJumpIslandNumber(), k) >= 1) break;
						}
						if (k == IslandInfo::Island_Num) {
							continue;
							//_enemy[j]->SetNextDecisionFlag(0);
						}
					}
					if (i == _enemy[j]->GetLastTouchIslandNumber())continue;
					//if (_enemy[j]->_onthThinkFlag == 1)continue;
					//if (!_enemy[j]->GetJumpMoveFlag())continue;

					int x = abs(_island[0]->GetPosX() - _island[i]->GetPosX());
					int y = abs(_island[0]->GetPosY() - _island[i]->GetPosY());
					//int xx = abs(_island[0]->GetPosX() - v_posX[j]);
					//int yy = abs(_island[0]->GetPosY() - v_posY[j]);
					//int xx = abs(_island[0]->GetPosX() - _enemy[j]->GetNextJumpPosX());
					//int yy = abs(_island[0]->GetPosY() - _enemy[j]->GetNextJumpPosY());
					int xx = abs(_island[0]->GetPosX() - v_x);
					int yy = abs(_island[0]->GetPosY() - v_y);
					//int vx, vy;
					if (x * x + y * y < xx * xx + yy * yy || !jumpPosibleFlag) {
						if (_enemy[j]->_dis_number == ENEMYTYPE_MONKEY && i != 0) { // サルだったら
							int k;
							for (k = 0; k < IslandInfo::Island_Num; k++) {
								if (_rope.GetConnectFlag(i, k) >= 1)break;
							}
							//_enemy[j]->SetPerceiveFlag(false);
							if (k != IslandInfo::Island_Num) { // ISLAND_NUMまで来なければつながっている
								_enemy[j]->SetPerceiveFlag(true);
								jumpImposibleFlag = true;
								//_enemy[j]->OffJumpMoveFlag();
								continue;
							}
							jumpImposibleFlag = false;
						}
						//if (!_enemy[j]->GetJumpMoveFlag())continue;
						//vx = _island[i]->GetPosX();
						//vy = _island[i]->GetPosY();
						int k;
						for (k = 0; k < EnemyInfo::Enemy_Num; k++) {
							if (j == k)continue;
							if (!_enemy[k]->GetLiveFlag() || _enemy[k]->GetDethDelayFlag())continue;
							if (_enemy[k]->GetRopeModeFlag())continue;
							if (_island[i]->GetPosX() == _enemy[k]->GetPosX() && _island[i]->GetPosY() == _enemy[k]->GetPosY()) {
								if (!_enemy[k]->GetJumpNowFlag()) {
									//_enemy[j]->OffJumpMoveFlag();
									jumpImposibleFlag = true;
									//rialJumpFlag = true;
									//if (vertualJumpFlag)jumpImposibleFlag = true;
									break;
								}
								//rialJumpFlag = true;
								//if (vertualJumpFlag)jumpImposibleFlag = true;
								//break;
							}
							if (_island[i]->GetPosX() == _enemy[k]->GetNextJumpPosX() && _island[i]->GetPosY() == _enemy[k]->GetNextJumpPosY()) {
								jumpImposibleFlag = true;
								//vertualJumpFlag = true;
								//if (rialJumpFlag)jumpImposibleFlag = true;
								break;
							}
						}
						if (k == EnemyInfo::Enemy_Num) {
							//v_posX[j] = vx;
							//v_posY[j] = vy;
							//v_islandNumber[j] = i;
							//_enemy[j]->SetNextJumpInfo(_island[i]->GetPosX(), _island[i]->GetPosY(), i);
							v_x = _island[i]->GetPosX();
							v_y = _island[i]->GetPosY();
							v_n = i;
							jumpPosibleFlag = true;
							jumpImposibleFlag = false;
						}
					}
				}
			}
			else if (!distanceFlag) {
				//if (_enemy[j]->_onthThinkFlag == 1)continue;
				//if (!_enemy[j]->GetJumpMoveFlag())continue;
				//if (_enemy[j]->GetNextDecisionFlag() == 1)continue;
				if (_enemy[j]->GetNextDecisionFlag() == 1 && _enemy[j]->_dis_number == ENEMYTYPE_MONKEY && i != 0) {
					int k;
					for (k = 0; k < IslandInfo::Island_Num; k++) {
						if (_rope.GetConnectFlag(_enemy[j]->GetNextJumpIslandNumber(), k) >= 1) break;
					}
					if (k == IslandInfo::Island_Num) {
						continue;
						//_enemy[j]->SetNextDecisionFlag(0);
					}
				}

				//auto x = abs(_island[i]->GetPosX() - v_posX[j]);
				//auto y = abs(_island[i]->GetPosY() - v_posY[j]);
				auto x = abs(_island[i]->GetPosX() - _enemy[j]->GetPosX());
				auto y = abs(_island[i]->GetPosY() - _enemy[j]->GetPosY());
				//auto xy = sqrt(x * x + y * y);
				if (x * x + y * y < v_dx * v_dx + v_dy * v_dy || !jumpPosibleFlag) {
					if (_enemy[j]->_dis_number == ENEMYTYPE_MONKEY && i != 0) { // サルだったら
						int k;
						for (k = 0; k < IslandInfo::Island_Num; k++) {
							if (_rope.GetConnectFlag(i, k) >= 1)break;
						}
						if (k != IslandInfo::Island_Num) { // ISLAND_NUMまで来なければつながっている
							_enemy[j]->SetPerceiveFlag(true);
							//_enemy[j]->OffJumpMoveFlag();
							jumpImposibleFlag = true;
							continue;
						}
						jumpImposibleFlag = false;
					}
					//if (!_enemy[j]->GetJumpMoveFlag())continue;
					int k;
					for (k = 0; k < EnemyInfo::Enemy_Num; k++) {
						if (j == k)continue;
						if (!_enemy[k]->GetLiveFlag() || _enemy[k]->GetDethDelayFlag())continue;
						if (_enemy[k]->GetRopeModeFlag())continue;
						if (_island[i]->GetPosX() == _enemy[k]->GetPosX() && _island[i]->GetPosY() == _enemy[k]->GetPosY()) {
							if (!_enemy[k]->GetJumpNowFlag()) {
								//rialJumpFlag = true;
								//if (vertualJumpFlag)jumpImposibleFlag = true;
								jumpImposibleFlag = true;
								break;
							}
							//jumpImposibleFlag = true;
							//rialJumpFlag = true;
							//if (vertualJumpFlag)jumpImposibleFlag = true;
							//break;
						}
						if (_island[i]->GetPosX() == _enemy[k]->GetNextJumpPosX() && _island[i]->GetPosY() == _enemy[k]->GetNextJumpPosY()) {
							//jumpImposibleFlag = true;
							//vertualJumpFlag = true;
							//if (rialJumpFlag)jumpImposibleFlag = true;
							jumpImposibleFlag = true;
							break;
						}
					}
					if (k != EnemyInfo::Enemy_Num)continue;
					v_dx = x;
					v_dy = y;
					v_x = _island[i]->GetPosX();
					v_y = _island[i]->GetPosY();
					v_n = i;
					jumpPosibleFlag = true;
					jumpImposibleFlag = false;
				}
			}
		}
		//if (jumpImposibleFlag && !jumpPosibleFlag)
		if (jumpImposibleFlag)
		//if(!jumpPosibleFlag)
			_enemy[j]->OffJumpMoveFlag();
		//_enemy[j]->_onthThinkFlag = true;
		//if (!distanceFlag) {
		//	//_enemy[j]->SetPerceiveFlag(true);
		//	//v_posX[j] = v_x;
		//	//v_posY[j] = v_y;
		//	//if (v_n != -1)
		//	//	v_islandNumber[j] = v_n;
		//	_enemy[j]->SetNextJumpInfo(v_x, v_y, v_n);
		//}
		if (jumpPosibleFlag) {
			//if (v_n == _enemy[j]->_stayIsland)
			//	_enemy[j]->OffJumpMoveFlag();
			//else
			if (v_n != _enemy[j]->_stayIsland)
				_enemy[j]->SetNextJumpInfo(v_x, v_y, v_n);
		}
		if (_enemy[j]->_dis_number != ENEMYTYPE_SLIME)continue;
		if (count > 0) {
			_enemy[j]->OnRopeModeFlag();
			_enemy[j]->SetAngle(max_angle);
			_enemy[j]->SetSpeed(cos(_enemy[j]->GetAngle()), sin(_enemy[j]->GetAngle()));
			_enemy[j]->SetLastTouchIslandNumber(_enemy[j]->_stayIsland);
		}
		else { // 折り返し移動処理
			bool lastCheck = 0;
			for (int k = 0; k < IslandInfo::Island_Num; k++) {
				if (k == _enemy[j]->GetLastTouchIslandNumber())continue;
				if (_rope.GetConnectFlag(_enemy[j]->_stayIsland, k) >= 3) {
					lastCheck = 1;
					break;
				}
			}
			if (lastCheck == 0 && _rope.GetConnectFlag(_enemy[j]->_stayIsland, _enemy[j]->GetLastTouchIslandNumber()) >= 3 && !_enemy[j]->GetRopeModeFlag()) {
				_enemy[j]->SetAngle(atan2(
					_island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosY() - _island[_enemy[j]->_stayIsland]->GetPosY(),
					_island[_enemy[j]->GetLastTouchIslandNumber()]->GetPosX() - _island[_enemy[j]->_stayIsland]->GetPosX()));
				_enemy[j]->SetSpeed(cos(_enemy[j]->GetAngle()), sin(_enemy[j]->GetAngle()));
				_enemy[j]->OnRopeModeFlag();
				_enemy[j]->SetLastTouchIslandNumber(_enemy[j]->_stayIsland);
			}
		}
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
		int ii = _enemy[i]->GetJumpMoveFlag();
		int iii = _enemy[i]->_atackModeFlag;
		int iiii = _enemy[i]->GetJumpNowFlag();
		if (_enemy[i]->GetNextDecisionFlag() == 0)continue;
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
			_enemy[i]->SetLastTouchIslandNumber(_enemy[i]->_stayIsland);
		}
		//if (_enemy[i]->GetPosX() == IslandInfo::Base_Island_PosX && _enemy[i]->GetPosY() == IslandInfo::Base_Island_PosY) {
		//	_enemy[i]->Attack();
		//	_player.Damage();
		//	_enemy[i]->Deth();
		//}
		
	}
	for (int i = 0; i < EnemyInfo::Enemy_Num; i++) {
		if (!_enemy[i]->GetLiveFlag() || _enemy[i]->GetDethDelayFlag())continue;
		if (_enemy[i]->GetPosX() <= IslandInfo::Base_Island_PosX + 2 && _enemy[i]->GetPosX() >= IslandInfo::Base_Island_PosX - 2
			&& _enemy[i]->GetPosY() <= IslandInfo::Base_Island_PosY + 2 && _enemy[i]->GetPosY() >= IslandInfo::Base_Island_PosY - 2) {
			_enemy[i]->Attack();
			_player.Damage();
			_enemy[i]->Deth();

			int shieldCount = 0;
			if (_player.GetHP() == 3) {
				for (int j = 0; j < SHIELDBREAKEFFECT_NUM; j++) {
					if (_shieldBreakEffect[j]->GetActiveFlag())continue;
					_shieldBreakEffect[j]->Instantiate(IslandInfo::Base_Island_PosX + 60, IslandInfo::Base_Island_PosY + 10);
					shieldCount++;
					if (shieldCount >= 30)break;
				}
			}
			if (_player.GetHP() == 2) {
				for (int j = 0; j < SHIELDBREAKEFFECT_NUM; j++) {
					if (_shieldBreakEffect[j]->GetActiveFlag())continue;
					_shieldBreakEffect[j]->Instantiate(IslandInfo::Base_Island_PosX - 60, IslandInfo::Base_Island_PosY + 10);
					shieldCount++;
					if (shieldCount >= 30)break;
				}
			}
			if (_player.GetHP() == 1) {
				for (int j = 0; j < SHIELDBREAKEFFECT_NUM; j++) {
					if (_shieldBreakEffect[j]->GetActiveFlag())continue;
					_shieldBreakEffect[j]->Instantiate(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY + 10);
					shieldCount++;
					if (shieldCount >= 30)break;
				}
			}
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

			int shieldCount = 0;
			if (_player.GetHP() == 3) {
				for (int j = 0; j < SHIELDBREAKEFFECT_NUM; j++) {
					if (_shieldBreakEffect[j]->GetActiveFlag())continue;
					_shieldBreakEffect[j]->Instantiate(IslandInfo::Base_Island_PosX + 60, IslandInfo::Base_Island_PosY + 10);
					shieldCount++;
					if (shieldCount >= 30)break;
				}
			}
			if (_player.GetHP() == 2) {
				for (int j = 0; j < SHIELDBREAKEFFECT_NUM; j++) {
					if (_shieldBreakEffect[j]->GetActiveFlag())continue;
					_shieldBreakEffect[j]->Instantiate(IslandInfo::Base_Island_PosX - 60, IslandInfo::Base_Island_PosY + 10);
					shieldCount++;
					if (shieldCount >= 30)break;
				}
			}
			if (_player.GetHP() == 1) {
				for (int j = 0; j < SHIELDBREAKEFFECT_NUM; j++) {
					if (_shieldBreakEffect[j]->GetActiveFlag())continue;
					_shieldBreakEffect[j]->Instantiate(IslandInfo::Base_Island_PosX, IslandInfo::Base_Island_PosY + 10);
					shieldCount++;
					if (shieldCount >= 30)break;
				}
			}
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
				for (int k = 0; k < 5; k++) {
					if (!_ropeLifeUpEffect[k]->GetActiveFlag())continue;
					_ropeLifeUpEffect[k]->WaitingFlagOf();
				}
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

	//if (CheckHitKey(KEY_INPUT_R)) {
	//	//Init();
	//	_gameOverFlag = 1;
	//	//_gameClearFlag = 1;
	//	//StopSoundMem(_sh_gameplay);
	//}

	//if (!_player.GetLive()) {
	//	//_sceneState = RESULT;
	//	_gameOverFlag = 1;
	//	_island[0]->_gameOverFlag = true;
	//}

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
	for (int i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		_ropeLifeDownEffect[i]->Update();
	}
	_rope.Update();
	for (int i = 0; i < 5; i++) {
		if (!_ropeLifeUpEffect[i]->GetActiveFlag())continue;
		_ropeLifeUpEffect[i]->Update();
	}
	for (int i = 0; i < SHIELDBREAKEFFECT_NUM; i++) {
		_shieldBreakEffect[i]->Update();
	}
	_thunderChargeUI.Update();
	_waveUpEffect.Update();

	if (CheckHitKey(KEY_INPUT_R)) {
		//Init();
		_gameOverFlag = 1;
		_island[0]->_gameOverFlag = true;
		//_gameClearFlag = 1;
		//StopSoundMem(_sh_gameplay);
	}
	if (!_player.GetLive()) {
		//_sceneState = RESULT;
		_gameOverFlag = 1;
		_island[0]->_gameOverFlag = true;
	}
}

void GameController::GameClearUpdate()
{
	if (_white_paramVol == 0) {
		StopSoundMem(_sh_gameplay);
	}
	if (_white_paramVol == 198) {
		PlaySoundMem(_sh_gameClear, DX_PLAYTYPE_BACK);
	}
	if (_white_paramVol < 200) {
		_white_paramVol += 3;
	}
	else {
		_nextCount++;
		_nextPosCount++;
		if (_gameclearAlphaCount < 255) {
			_gameclearAlphaCount += 3;
		}
		else if (_gameclear_thanksAlphaCount < 255) {
			_gameclear_thanksAlphaCount += 3;
		}
		int posX = 550;
		int posY = 735;
		int width = 350;
		int height = 60;
		//MyDrawTurn::Instance().SetDrawItem(posX, posY, 0, 0.92, DRAWTYPE_DRAWBOX, 0, 0, BLENDMODE_NOBLEND, 0, posX + width, posY + height);
		if (_mouseCount_Left == -1 && _nextCount > 230) {
			if (_mousePosX_Left >= posX && _mousePosX_Left <= posX + width
				&& _mousePosY_Left >= posY && _mousePosY_Left <= posY + height) {
				PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
				_sceneState = TITLE;
				Init();
			}
		}
	}
}

void GameController::GameClearDraw()
{
	MyDrawTurn::Instance().SetDrawBrightItem(0, 0, _gh_white, 0.9f, 255, 255, 255, BLENDMODE_ALPHA, _white_paramVol);

	if (_white_paramVol >= 200) {
		MyDrawTurn::Instance().SetDrawBrightItem(0, 0, _gh_gameclear, 0.91f, 255, 255, 255, BLENDMODE_ALPHA, _gameclearAlphaCount);
		MyDrawTurn::Instance().SetDrawBrightItem(0, 0, _gh_thanks, 0.91f, 255, 255, 255, BLENDMODE_ALPHA, _gameclear_thanksAlphaCount);
		if(_nextCount > 230)
		MyDrawTurn::Instance().SetDrawItem(WindowInfo::Screen_Width - 70 + cos(_nextPosCount / 6) * 3, WindowInfo::Screen_Height - 40, _gh_next, 0.91f,DRAWTYPE_DRAWROTAGRAPH,1,90 * (3.1415 / 180));
	}
}

void GameController::GameOverUpdate()
{
	if (_black_paramVol == 0) {
		StopSoundMem(_sh_gameplay);
	}
	if (_black_paramVol == 198) {

	}
	if (_black_paramVol < 200) {
		_black_paramVol += 3;
	}
	else {
		_animCount_crystal++;
		if (_animCount_crystal % 10 == 0 && _animPos_crystal < 13) {
			_animPos_crystal++;
			if (_animPos_crystal == 13) {
				_animCount_crystal = 0;
			}
			return;
		}
		if (_animCount_crystal < 30 && _animPos_crystal == 13) return;
	
		if(_animCount_crystal == 30 && _animPos_crystal == 13)
			PlaySoundMem(_sh_gameOver, DX_PLAYTYPE_BACK);

		_nextCount++;
		_nextPosCount++;
		if (_gameoverAlphaCount < 255) {
			_gameoverAlphaCount += 1;
		}
		
		int posX = 450;
		int posY = 620;
		int width = 370;
		int height = 80;
		//MyDrawTurn::Instance().SetDrawItem(450, 620, 0, 0.92, DRAWTYPE_DRAWBOX, 0, 0, BLENDMODE_NOBLEND, 0, 450 + 370, 620 + 80);
		if (_mouseCount_Left == -1 && _nextCount > 60) {
			if (_mousePosX_Left >= posX && _mousePosX_Left <= posX + width
				&& _mousePosY_Left >= posY && _mousePosY_Left <= posY + height) {
				StopSoundMem(_sh_gameOver);
				PlaySoundMem(_sh_click, DX_PLAYTYPE_BACK);
				_sceneState = TITLE;
				Init();
			}
		}
	}
}

void GameController::GameOverDraw()
{
	MyDrawTurn::Instance().SetDrawBrightItem(0, 0, _gh_black, 0.9f, 0, 0, 0, BLENDMODE_ALPHA, _black_paramVol);
	MyDrawTurn::Instance().SetDrawItem(_island[0]->GetPosX() - 26, _island[0]->GetPosY() - 34 + 40, _gh_crystal[_animPos_crystal], 0.91f);
	
	//if (_black_paramVol >= 200) {
	if(_animCount_crystal > 30 && _animPos_crystal == 13){
		MyDrawTurn::Instance().SetDrawBrightItem(0, 0, _gh_gameover, 0.91f, _gameoverAlphaCount, _gameoverAlphaCount, _gameoverAlphaCount,BLENDMODE_ALPHA, 255);
		MyDrawTurn::Instance().SetDrawBrightItem(0, 0, _gh_result, 0.91f, _gameoverAlphaCount, _gameoverAlphaCount, _gameoverAlphaCount, BLENDMODE_ALPHA, 255);
		MyDrawTurn::Instance().SetDrawBrightItem(250, 500, _gh_resultWave, 0.91f, _gameoverAlphaCount, _gameoverAlphaCount, _gameoverAlphaCount, BLENDMODE_ALPHA, 255);
		_drawNumber.DrawBright(700, 485, _wave, SETDRAWNUM_RESULTWAVE, _gameoverAlphaCount, _gameoverAlphaCount, _gameoverAlphaCount, BLENDMODE_ALPHA, 255);
		if (_nextCount > 60)
		MyDrawTurn::Instance().SetDrawItem(WindowInfo::Screen_Width - 140 + cos(_nextPosCount / 6) * 3, WindowInfo::Screen_Height - 140, _gh_next, 0.91f, DRAWTYPE_DRAWROTAGRAPH, 1, 90 * (3.1415 / 180));
	}
}

void GameController::Draw()
{
	DrawGraph(0, 0, _gh_background, FALSE);
	DrawExtendGraph(_cloud_posX, _cloud_posY, _cloud_posX + WindowInfo::Screen_Width, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawExtendGraph(_cloud_posX - WindowInfo::Screen_Width, _cloud_posY, _cloud_posX, _cloud_posY + WindowInfo::Screen_Height, _gh_cloud, TRUE);
	DrawGraph(0, 0, _gh_background2, TRUE);
	MyDrawTurn::Instance().SetDrawItem(0, 0, _gh_UIbar, 0.82f);
	int count;
	for (count = 0; count < IslandInfo::Island_Num; count++) {
		int j;
		for (j = 0; j < IslandInfo::Island_Num; j++) {
			if (_rope.GetConnectFlag(count, j) != 0)break;
		}
		if (j != IslandInfo::Island_Num)break;
	}
	if (count == IslandInfo::Island_Num && _now_player_num != 0) {
		_UIstartCount++;
	}
	else {
		_UIstartCount = 0;
	}
	if (_UIstartCount > 120)
		MyDrawTurn::Instance().SetDrawItem(IslandInfo::Base_Island_PosX + 100 + cos(_time.GetGameTime() / 6) * 3, IslandInfo::Base_Island_PosY, _gh_UIStart, 0.8f);
	_thunderChargeUI.Draw();
	//DrawGraph(_cloud_posX, _cloud_posY, _gh_cloud, TRUE);
	//DrawGraph(_cloud_posX - _cloud_width, _cloud_posY, _gh_cloud, TRUE);
	//DrawFormatString(10, 610, GetColor(0, 0, 0), "hp : %d", _player.GetHP());
	if (_mouseCount_Left > 1) {
		int i;
		for (i = 0; i < IslandInfo::Island_Num; i++) {
			if (_rope.GetConnectFlag(_now_player_num, i) != 0)break;
		}
		if (i != IslandInfo::Island_Num && _rope.GetRopeLife() > 0) {
			MyDrawTurn::Instance().SetDrawBrightItem(_island[_now_player_num]->GetPosX(), _island[_now_player_num]->GetPosY(), 0, 0.5, 100, 255, 100, BLENDMODE_NOBLEND, 0, DRAWTYPE_DRAWLINE, 0, _mousePosX_Left, _mousePosY_Left);
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
	MyDrawTurn::Instance().SetDrawItem(42 + 7, 670 - 4, _gh_thunderUI[_animPos_thunderUI], 0.83f);
	//DrawFormatString(10, 570, GetColor(0, 0, 0), "WAVE : %d", _wave);

	if (!_waveUpEffect.GetActiveFlag()) {
		MyDrawTurn::Instance().SetDrawItem(10, 20, _gh_wave, 0.8f);
		if (_wave > 10) {
			_drawNumber.Draw(230, 10, _wave - 1, SETDRAWNUM_WAVE);
		}
		else {
			_drawNumber.Draw(230, 10, _wave, SETDRAWNUM_WAVE);
		}
	}

	int ropeLife = 0;
	for (int i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		if (ropeLife < _rope.GetRopeLife()) {
			MyDrawTurn::Instance().SetDrawItem(240 + (40 * i) - 42, 766 - 55, _gh_tuta_life_active, 0.83f);
		}
		//else{
		else if(ropeLife < _rope.GetMaxRopeLife()){
			MyDrawTurn::Instance().SetDrawItem(240 + (40 * i) - 42, 766 - 55, _gh_tuta_life_inactive, 0.83f);
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
		//DrawFormatString(_island[i]->GetPosX() + 30, _island[i]->GetPosY() - 30, GetColor(0, 0, 255), "%d", i);
	}
	_island[0]->Draw();
	for (int i = 0; i < RopeInfo::Rope_MaxLife; i++) {
		_ropeLifeDownEffect[i]->Draw();
	}
	int checkIsland;
	for (checkIsland = 0; checkIsland < IslandInfo::Island_Num; checkIsland++) {
		if (_now_player_num == 0)break;
		if (_rope.GetConnectFlag(_now_player_num, checkIsland) >= 1) break;
	}
	if (checkIsland != IslandInfo::Island_Num) { // 自分のいる島がどこかとつながっているか拠点にいるなら
		for (int i = 0; i < IslandInfo::Island_Num; i++) {
			if (_island[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
				DrawLine(_player.GetPosX(), _player.GetPosY(), _island[i]->GetPosX(), _island[i]->GetPosY(), GetColor(150, 150, 150), 3);
			}
		}
	}
	//for (int i = 0; i < IslandInfo::Island_Num; i++) {
	//	if (_island[i]->DistanseCheck(_player.GetPosX(), _player.GetPosY())) {
	//		//bool connectCheck = false;
	//		//for (int j = 0; j < IslandInfo::Island_Num; j++) {
	//		//	if (//_rope.GetConnectFlag(i, j) ||			// 反対側からもロープをかけられる
	//		//		_rope.GetConnectFlag(_now_player_num, j) >= 3)	// 自分がいる島と繋がっているか
	//		//	{
	//		//		connectCheck = true;
	//		//	}
	//		//}
	//		//if (!connectCheck) {
	//		//	if (_island[_now_player_num]->GetPosX() == IslandInfo::Base_Island_PosX && _island[_now_player_num]->GetPosY() == IslandInfo::Base_Island_PosY) {

	//		//	}
	//		//	else {
	//		//		continue;
	//		//	}
	//		//}
	//		////if (_island[_now_player_num]->StateCheck_BURN())continue;
	//		DrawLine(_player.GetPosX(), _player.GetPosY(), _island[i]->GetPosX(), _island[i]->GetPosY(), GetColor(150, 150, 150), 3);
	//	}
	//}
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
			//DrawFormatString(_island[i]->GetPosX(), _island[i]->GetPosY(), GetColor(0, 0, 0), "%d", i);
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
	for (int i = 0; i < 5; i++) {
		if (!_ropeLifeUpEffect[i]->GetActiveFlag())continue;
			_ropeLifeUpEffect[i]->Draw();
	}
	for (int i = 0; i < SHIELDBREAKEFFECT_NUM; i++) {
		_shieldBreakEffect[i]->Draw();
	}
	_waveUpEffect.Draw();
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
	case 17:
		maximum = 2;
		break;
	case 34:
		maximum = 5;
		break;
	case 42:
		maximum = 2;
		break;
	case 48:
		maximum = 6;
		break;
	case 57:
		maximum = 2;
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
			if (counter % 3 == 1)x = -20, y = -30;
			if (counter % 3 == 2)x = 40, y = 0;
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
	_enemySpawnNumber[2] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[3] = ENEMYTYPE_SLIME; 
	_enemySpawnNumber[4] = ENEMYTYPE_SLIME;

	_enemySpawnNumber[5] = ENEMYTYPE_SLIME; //3  
	_enemySpawnNumber[6] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[7] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[8] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[9] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[10] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[11] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[12] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[13] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[14] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[15] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[16] = ENEMYTYPE_DEMON;

	_enemySpawnNumber[17] = ENEMYTYPE_MONKEY; //2
	_enemySpawnNumber[18] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[19] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[20] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[21] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[22] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[23] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[24] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[25] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[26] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[27] = ENEMYTYPE_SLIME;

	_enemySpawnNumber[28] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[29] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[30] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[31] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[32] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[33] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[34] = ENEMYTYPE_SLIME; //5
	_enemySpawnNumber[35] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[36] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[37] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[38] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[39] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[40] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[41] = ENEMYTYPE_MONKEY;
	
	_enemySpawnNumber[42] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[43] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[44] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[45] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[46] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[47] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[48] = ENEMYTYPE_DEMON; //6
	_enemySpawnNumber[49] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[50] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[51] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[52] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[53] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[54] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[55] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[56] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[57] = ENEMYTYPE_MONKEY; //2
	_enemySpawnNumber[58] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[59] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[60] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[61] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[62] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[63] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[64] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[65] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[66] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[67] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[68] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[69] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[70] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[71] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[72] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[73] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[74] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[75] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[76] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[77] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[78] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[79] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[80] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[81] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[82] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[83] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[84] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[85] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[86] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[87] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[88] = ENEMYTYPE_MONKEY;

	_enemySpawnNumber[89] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[90] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[91] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[92] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[93] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[94] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[95] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[96] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[97] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[98] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[99] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[100] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[101] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[102] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[103] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[104] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[105] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[106] = ENEMYTYPE_SLIME;

	_enemySpawnNumber[107] = ENEMYTYPE_SLIME; //3
	_enemySpawnNumber[108] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[109] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[110] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[111] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[112] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[113] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[114] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[115] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[116] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[117] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[118] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[119] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[120] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[121] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[122] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[123] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[124] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[125] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[126] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[127] = ENEMYTYPE_DEMON;

	_enemySpawnNumber[128] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[129] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[130] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[131] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[132] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[133] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[134] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[135] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[136] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[137] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[138] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[139] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[140] = ENEMYTYPE_SLIME; //6
	_enemySpawnNumber[141] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[142] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[143] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[144] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[145] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[146] = ENEMYTYPE_MONKEY; //3
	_enemySpawnNumber[147] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[148] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[149] = ENEMYTYPE_DEMON; //3
	_enemySpawnNumber[150] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[151] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[152] = ENEMYTYPE_MONKEY; //6
	_enemySpawnNumber[153] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[154] = ENEMYTYPE_MONKEY;
	_enemySpawnNumber[155] = ENEMYTYPE_SLIME;
	_enemySpawnNumber[156] = ENEMYTYPE_DEMON;
	_enemySpawnNumber[157] = ENEMYTYPE_SLIME;
}
