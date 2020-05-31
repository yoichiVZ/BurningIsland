#include <DxLib.h>
#include "Island.h"

#include "MyDrawTurn.h"

#include "IslandInfo.h"
#include "PlayerInfo.h"

#include "Player.h"

Island::Island()
{
	_gh_island = LoadGraph("Resource\\Image\\sima1.png");
	_gh_burnIsland = LoadGraph("Resource\\Image\\kurosima.png");
	_gh_base = LoadGraph("Resource\\Image\\yugudorasiru1.png");
	_gh_base_crystal = LoadGraph("Resource\\Image\\yugudorasiru2.png");
	_gh_rightEfect01 = LoadGraph("Resource\\Image\\Efect01.png");
	LoadDivGraph("Resource\\Image\\moerusima.png", 10, 5, 2, 100, 100, _gh_burningIsland);
	LoadDivGraph("Resource\\Image\\saisei.png", 8, 4, 2, 80, 80, _gh_revivalingIsland);
	_sh_fire = LoadSoundMem("Resource\\Sound\\fire.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_fire);
	GetGraphSize(_gh_island, &_width, &_height);
	GetGraphSize(_gh_base, &_base_width, &_base_height);
	Init();
	for (int i = 0; i < 10; i++) {
		_yugudorasiruParticle[i] = new YugudorasiruParticle();
	}
}

Island::~Island()
{
	for (int i = 0; i < 10; i++) {
		delete _yugudorasiruParticle[i];
	}
}

void Island::Init()
{
	_posX = 0; _posY = 0;
	_rotation = IslandInfo::Island_Rotation;
	_distanseFlag = false;
	_playerStayFlag = false;
	_islandState = GRASS;
	_fireCount = 0;
	_burnCount = 0;
	_fireStartFlag = false;
	_fireStartCount = 0;
	_extinguishedFlag = false;
	_animPos_burningIsland = 0;
	_animCount_burningIslnad = 0;
	_animPos_revivalingIsland = 0;
	_animCount_revivalingIsland = 0;
	_nowChoiceDistance = 0;
	_nowChoiceDistanceCount = 0;
	_nowChoiceFlag = false;
	_particle_activeCount = 0;
	_particle_firstActiveCount = GetRand(90) + 30;
}

void Island::Update()
{
	if (_posX == IslandInfo::Base_Island_PosX && _posY == IslandInfo::Base_Island_PosY) {
		_particle_activeCount++;
		if (_particle_activeCount > _particle_firstActiveCount) {
			for (int i = 0; i < YUGUDORASIRU_PARITCLE_NUM; i++) {
				if (_yugudorasiruParticle[i]->GetActive())continue;
				_yugudorasiruParticle[i]->SetActive(_posX, _posY + 40);
				_particle_activeCount = 0;
				_particle_firstActiveCount = GetRand(90) + 30;
				break;
			}
		}
		for (int i = 0; i < YUGUDORASIRU_PARITCLE_NUM; i++) {
			if (!_yugudorasiruParticle[i]->GetActive())continue;
			_yugudorasiruParticle[i]->Move();
		}
	}
	if (_fireStartFlag) {
		_fireStartCount++;
		_burnCount = 0;
	}
	if (_fireStartCount > 10) {
		_fireStartCount = 0;
		_fireStartFlag = false;
		Burning();
	}
	switch (_islandState) {
	case GRASS:
		break;

	case FIRE:
		if (_fireCount == 0)_animPos_burningIsland = 0;
		_fireCount++;
		if (_fireCount > 120) {
			_islandState = BURN;
			_fireCount = 0;
			_extinguishedFlag = true;
		}
		if (_fireCount % 12 == 0) {
			_animPos_burningIsland++;
		}
		if (_animPos_burningIsland > 10 - 1)_animPos_burningIsland = 10 - 1;
		break;

	case BURN:
		_burnCount++;
		if (_burnCount < 600 - (8 - 1) * 3) {
			_animPos_revivalingIsland = 0;
		}
		else if (_burnCount % 3 == 0) {
			_animPos_revivalingIsland++;
		}
		if (_animPos_revivalingIsland > 8 - 1)_animPos_revivalingIsland = 8 - 1;
		if (_burnCount > 600) {
			_islandState = GRASS;
			_burnCount = 0;
		}
		break;
		
	default:
		break;
	}
	if (_playerStayFlag) {
		_nowChoiceDistanceCount++;
		if (_nowChoiceDistanceCount % 6 == 0) {
			if (_nowChoiceFlag) {
				_nowChoiceDistance--;
			}
			else {
				_nowChoiceDistance++;
			}
		}
		//nowChoice_distance = 5;
	}
	else {
		_nowChoiceDistance = 0;
		_nowChoiceDistanceCount = 0;
		_nowChoiceFlag = false;
	}
}

void Island::Draw()
{
	//if (_islandState == GRASS)DrawCircle(_posX, _posY, _rotation, GetColor(255, 255, 255), TRUE);
	//int nowChoice_distance = 0;
	int distance = 0;
	if (_nowChoiceDistance > 4) {
		_nowChoiceFlag = true;
	}
	if (_nowChoiceDistance < -1) {
		_nowChoiceFlag = false;
	}
	if (_nowChoiceDistance >= 3) {
		distance = 3 - _nowChoiceDistance;
	}
	if (_nowChoiceDistance <= 0) {
		distance = 0 - _nowChoiceDistance;
	}
	if (_posX == IslandInfo::Base_Island_PosX && _posY == IslandInfo::Base_Island_PosY) {
		//DrawGraph(_posX - _base_width / 2, _posY - _base_height / 2, _gh_base, TRUE);
		MyDrawTurn::Instance().SetDrawItem(_posX - _base_width / 2, _posY - _base_height / 2 + _nowChoiceDistance + distance + 40, _gh_base, 0.31f);
		MyDrawTurn::Instance().SetDrawItem(_posX - 15, _posY - 24 + _nowChoiceDistance + distance + 40, _gh_base_crystal, 0.32f);
		MyDrawTurn::Instance().SetDrawBrightItem(_posX - 60, _posY - 60 + _nowChoiceDistance + distance + 40, _gh_rightEfect01, 0.311f, 100, 255, 100,
			BLENDMODE_ADD, 180, DRAWTYPE_DRAWEXTENDGRAPH, 0, _posX + 60, _posY + 60 + _nowChoiceDistance + distance + 40);
		for (int i = 0; i < YUGUDORASIRU_PARITCLE_NUM; i++) {
			if (!_yugudorasiruParticle[i]->GetActive())continue;
				_yugudorasiruParticle[i]->Draw();
		}
	}
	else {
		if (_islandState == GRASS) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2, _posY - _height / 2 + _nowChoiceDistance + distance, _gh_island, 0.2f);
		}
		if (_islandState == FIRE) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2 - 10, _posY - _height / 2 - 10 + _nowChoiceDistance, _gh_burningIsland[_animPos_burningIsland], 0.2f);
		}
		if (_islandState == BURN)MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2, _posY - _height / 2 + _nowChoiceDistance, _gh_revivalingIsland[_animPos_revivalingIsland], 0.2f);
	}

	//if (_distanseFlag) {
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
	//	if (_playerStayFlag)
	//		DrawCircle(_posX, _posY, _rotation, GetColor(0, 255, 0), TRUE);
	//	else
	//		DrawCircle(_posX, _posY, _rotation, GetColor(0, 155, 0), TRUE);
	//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//}
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

	if (x * x + y * y <= (PlayerInfo::Player_Rope_Distance + IslandInfo::Island_Rotation) * (PlayerInfo::Player_Rope_Distance + IslandInfo::Island_Rotation)) {
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

	if (x * x + y * y <= (PlayerInfo::Player_Rotation + IslandInfo::Island_Rotation) * (PlayerInfo::Player_Rotation + IslandInfo::Island_Rotation)) {
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

	if (x * x + y * y <= (PlayerInfo::Player_Rope_Distance + IslandInfo::Island_Rotation) * (PlayerInfo::Player_Rope_Distance + IslandInfo::Island_Rotation)) {
		return true;
	}

	return false;
}

bool Island::EnemyStayCheck(int ex, int ey)
{
	auto x = abs(ex - _posX);
	auto y = abs(ey - _posY);

	if (x * x + y * y <= (PlayerInfo::Player_Rotation + IslandInfo::Island_Rotation) * (PlayerInfo::Player_Rotation + IslandInfo::Island_Rotation)) {
		return true;
	}

	return false;
}

void Island::CrossCheck(Island* island)
{
	//DrawLine(_posX, _posY, island->_posX, island->_posY, GetColor(150, 150, 150), 3);

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
		PlaySoundMem(_sh_fire, DX_PLAYTYPE_BACK);
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

bool Island::ExtinguishedCheck()
{
	if (_extinguishedFlag) {
		_extinguishedFlag = false;
		return true;
	}
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

int Island::GetWidth()
{
	return _width;
}

int Island::GetHeight()
{
	return _height;
}

int Island::GetFireStartflag()
{
	return _fireStartFlag;
}

void Island::MoveX(int num)
{
	if (num == 0) {
		_posX--;
		return;
	}
	_posX++;
}

void Island::MoveY(int num)
{
	if (num == 0) {
		_posY--;
		return;
	}
	_posY++;
}
