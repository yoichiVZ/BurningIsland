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
	_gh_base = LoadGraph("Resource\\Image\\kyoten.png");
	LoadDivGraph("Resource\\Image\\moerusima.png", 10, 5, 2, 100, 100, _gh_burningIsland);
	LoadDivGraph("Resource\\Image\\saisei.png", 8, 4, 2, 80, 80, _gh_revivalingIsland);
	_sh_fire = LoadSoundMem("Resource\\Sound\\fire.mp3");
	GetGraphSize(_gh_island, &_width, &_height);
	GetGraphSize(_gh_base, &_base_width, &_base_height);
	Init();
}

Island::~Island()
{
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
}

void Island::Update()
{
	if (_fireStartFlag) {
		_fireStartCount++;
		_burnCount = 0;
	}
	if (_fireStartCount > 10) {
		_fireStartCount = 0;
		_fireStartFlag = false;
		Burning();
	}
	//if (_islandState == FIRE) {
	//	_fireCount++;
	//	if (_fireCount > 120) {
	//		_islandState = BURN;
	//		_fireCount = 0;
	//		_extinguishedFlag = true;
	//	}
	//}
	//else if (_islandState == BURN) {
	//	_burnCount++;
	//	if (_burnCount > 600) {
	//		_islandState = GRASS;
	//		_burnCount = 0;
	//	}
	//}
	//else if (_islandState == GRASS) {
	//	if (_fireStartFlag) {
	//		if (_fireStartCount % 2 == 0)_animPos_burningIslnad++;
	//	}
	//}
	switch (_islandState) {
	case GRASS:
		//if (_fireStartFlag) {
		//	if (_fireStartCount % 2 == 0)_animPos_burningIslnad++;
		//}
		break;

	case FIRE:
		if (_fireCount == 0)_animPos_burningIsland = 0;
		_fireCount++;
		if (_fireCount > 120) {
			_islandState = BURN;
			_fireCount = 0;
			_extinguishedFlag = true;
		}

		//if (_animPos_burningIslnad < 5)_animPos_burningIslnad = 5;
		//if (_fireCount < 110) {
		//	if (_fireCount % 2 == 0)_animPos_burningIslnad++;
		//	if (_animPos_burningIslnad > 10)_animPos_burningIslnad = 5;
		//}
		//else {
		//	if (_fireCount == 110)_animPos_burningIslnad = 10;
		//	else {
		//		if (_fireCount % 2 == 0)_animPos_burningIslnad++;
		//	}
		//}
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
}

void Island::Draw()
{
	//if (_islandState == GRASS)DrawCircle(_posX, _posY, _rotation, GetColor(255, 255, 255), TRUE);
	//int nowChoice_distance = 0;
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
		MyDrawTurn::Instance().SetDrawItem(_posX - _base_width / 2, _posY - _base_height / 2 + _nowChoiceDistance + distance, _gh_base, 0.31f);
	}
	else {
		//if (_islandState == GRASS)DrawGraph(_posX - _width / 2, _posY - _height / 2, _gh_island, TRUE);
		//if (_islandState == FIRE)DrawCircle(_posX, _posY, _rotation, GetColor(200, 0, 0), TRUE);
		//if (_islandState == BURN)DrawCircle(_posX, _posY, _rotation, GetColor(100, 100, 100), TRUE);
		if (_islandState == GRASS) {
			//if (_fireStartFlag)
				//MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2, _posY - _height / 2, _gh_burningIsland[_animPos_burningIslnad], 0.2f);
			//else
				MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2, _posY - _height / 2 + _nowChoiceDistance + distance, _gh_island, 0.2f);
		}
		if (_islandState == FIRE) {
			//if (_animPos_burningIslnad < 5)_animPos_burningIslnad = 5;
			//if (_fireCount < 110) {
			//	if (_fireCount % 2 == 0)_animPos_burningIslnad++;
			//	if (_animPos_burningIslnad > 10)_animPos_burningIslnad = 5;
			//}
			//else {
			//	if (_fireCount == 110)_animPos_burningIslnad = 10;
			//	else {
			//		if (_fireCount % 2 == 0)_animPos_burningIslnad++;
			//	}
			//}
			MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2 - 10, _posY - _height / 2 - 10 + _nowChoiceDistance, _gh_burningIsland[_animPos_burningIsland], 0.2f);
		}
		if (_islandState == BURN)MyDrawTurn::Instance().SetDrawItem(_posX - _width / 2, _posY - _height / 2 + _nowChoiceDistance, _gh_revivalingIsland[_animPos_revivalingIsland], 0.2f);
	}

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

	//DrawBox(_posX - IslandInfo::Island_Rotation, _posY - IslandInfo::Island_Rotation, 
	//	_posX + IslandInfo::Island_Rotation, _posY + IslandInfo::Island_Rotation, GetColor(255, 0, 0), TRUE);
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
	DrawLine(_posX, _posY, island->_posX, island->_posY, GetColor(150, 150, 150), 3);

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
