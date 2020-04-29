#include <DxLib.h>
#include "Rope.h"
#include "RopeInfo.h"

Rope::Rope()
{
	Init();
}

Rope::~Rope()
{
}

void Rope::Init()
{
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			_connectFlag[i][j] = false;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = false;
			_fireStartCount[i][j] = 0;
			_fireStartFlag[i][j] = false;
		}
	}
	_maxRopeLife = RopeInfo::Rope_Life;
	AllRecovery();
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
				_fireStartFlag[i][j] = false;
				Burn(i , j);
			}
			if (_fireFlag[i][j]) {
				_fireCount[i][j]++;
			}
			if (_fireCount[i][j] > RopeInfo::Fire_Count) {
				_fireCount[i][j] = 0;
				_fireFlag[i][j] = false;
				_connectFlag[i][j] = false;
			}
		}
	}
	if (_ropeLife <= 0) {
		AllDelete();
	}
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
	_connectFlag[island1][island2] = true;
	_connectFlag[island2][island1] = true;
}

void Rope::AllDelete()
{
	for (int i = 0; i < IslandInfo::Island_Num; i++) {
		for (int j = 0; j < IslandInfo::Island_Num; j++) {
			_connectFlag[i][j] = false;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = false;
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

void Rope::AllRecovery()
{
	_ropeLife = _maxRopeLife;
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
	_maxRopeLife += 1;
}

void Rope::Ignition(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return;
	_fireStartFlag[island1][island2] = true;
	_fireStartFlag[island2][island1] = true;

}

void Rope::Burn(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return;
	_fireFlag[island1][island2] = true;
	_fireFlag[island2][island1] = true;
}

bool Rope::GetConnectFlag(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return false;
	if (_connectFlag[island1][island2] || _connectFlag[island2][island1]) {
		return true;
	}
	return false;
}

bool Rope::GetFireFlag(int island1, int island2)
{
	if (island1 < 0 || island1 >= IslandInfo::Island_Num || island2 < 0 || island2 >= IslandInfo::Island_Num)return false;
	if (_fireFlag[island1][island2] || _fireFlag[island2][island1]) {
		return true;
	}
	return false;
}

int Rope::GetRopeLife()
{
	return _ropeLife;
}
