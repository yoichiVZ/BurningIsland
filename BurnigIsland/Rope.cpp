#include <DxLib.h>
#include "Rope.h"
#include "RopeInfo.h"

Rope::Rope()
{
	_sh_tuta = LoadSoundMem("Resource\\Sound\\tuta.mp3");
	ChangeVolumeSoundMem(255 * 30 / 100, _sh_tuta);
	Init();
}

Rope::~Rope()
{
}

void Rope::Init()
{
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			_connectFlag[i][j] = 0;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = 0;
			_fireStartCount[i][j] = 0;
			_fireStartFlag[i][j] = 0;
			_posX[i][j] = 0;
			_posY[i][j] = 0;
			_moveCount[i][j] = 0;
		}
	}
	_maxRopeLife = RopeInfo::Rope_Life;
	AllRecovery(0);
}

void Rope::Update()
{
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			if (_fireStartFlag[i][j]) {
				_fireStartCount[i][j]++;
			}
			if (_fireStartCount[i][j] > RopeInfo::Fire_Start_Count) {
				_fireStartCount[i][j] = 0;
				_fireStartFlag[i][j] = 0;
				Burn(i , j);
			}

			if (_fireFlag[i][j]) {
				_fireCount[i][j]++;
			}
			if (_fireCount[i][j] > RopeInfo::Fire_Count) {
				_fireCount[i][j] = 0;
				_fireFlag[i][j] = 0;
				_connectFlag[i][j] = 0;
				_connectFlag[j][i] = 0;
			}
		}
	}
	//if (_ropeLife <= 0) {
	//	AllDelete();
	//}
}

void Rope::Draw()
{
}

void Rope::All()
{
	Update();
}

void Rope::Connect(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return;
	_connectFlag[island1][island2] = 1;
	//_connectFlag[island2][island1] = 1;
	PlaySoundMem(_sh_tuta, DX_PLAYTYPE_BACK);
}

void Rope::ConnectFinished(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return;
	_connectFlag[island1][island2] = 2;
	//_connectFlag[island2][island1] = 2;
}

void Rope::AllDelete()
{
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			_connectFlag[i][j] = 0;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = 0;
		}
	}
	_ropeLife = _maxRopeLife;
}

void Rope::Minus()
{
	_ropeLife--;
	if (_ropeLife < 0) {
		_ropeLife = 0;
	}
}

void Rope::AllRecovery(int ropeNum)
{
	_ropeLife = _maxRopeLife - ropeNum;
}

void Rope::Recovery()
{
	_ropeLife++;
	if (_ropeLife > _maxRopeLife) {
		_ropeLife = _maxRopeLife;
	}
}

void Rope::AddMaxLife()
{
	if(_maxRopeLife < RopeInfo::Rope_MaxLife)
	_maxRopeLife += 1;
}

void Rope::Ignition(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return;
	_fireStartFlag[island1][island2] = true;
	//_fireStartFlag[island2][island1] = true;
}

void Rope::Burn(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return;
	_fireFlag[island1][island2] = true;
	//_fireFlag[island2][island1] = true;
}

int Rope::GetConnectFlag(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return false;
	if (_connectFlag[island1][island2] == 1) { // �����̓�����q�����Ă���Œ�
		return 1;
	}
	if (_connectFlag[island2][island1] == 1) { // �����̓��Ɍq�����Ă���Œ�
		return 2;
	}
	if (_connectFlag[island1][island2] == 2) { // �����̓�����q����I�����
		return 3;
	}
	if (_connectFlag[island2][island1] == 2) { // �����̓��Ɍq����I�����
		return 4;
	}
	return 0; // �q�����ĂȂ�
}

int Rope::GetFireFlag(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return false;
	if (_fireFlag[island1][island2] == 1) { // �����̓�����R���Ă���
		return 1;
	}
	if (_fireFlag[island2][island1] == 1) { // ����̓�����R���Ă���
		return 2;
	}
	//if (_fireFlag[island1][island2] || _fireFlag[island2][island1]) {
	//	return true;
	//}
	return false;
}

int Rope::GetFireStartFlag(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return false;
	if (_fireStartFlag[island1][island2] == 1) { // �����̓�����R���n�߂Ă���
		return 1;
	}
	if (_fireStartFlag[island2][island1] == 1) { // ����̓�����R���n�߂Ă���
		return 2;
	}
	//if (_fireStartFlag[island1][island2] || _fireStartFlag[island2][island1]) {
	//	return true;
	//}
	return false;
}

int Rope::GetRopeLife()
{
	return _ropeLife;
}

int Rope::GetMaxRopeLife()
{
	return _maxRopeLife;
}
