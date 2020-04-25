#include <DxLib.h>
#include "Rope.h"

Rope::Rope()
{
	Init();
}

Rope::~Rope()
{
}

void Rope::Init()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			_connectData[i][j] = false;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = false;
		}
	}
	AllRecovery();
}

void Rope::Update()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			if (_fireFlag[i][j]) {
				_fireCount[i][j]++;
			}
			if (_fireCount[i][j] > 120) {
				_fireCount[i][j] = 0;
				_fireFlag[i][j] = false;
				_connectData[i][j] = false;
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
	if (island1 < 0 || island1 >= ISLAND_NUM || island2 < 0 || island2 >= ISLAND_NUM)return;
	_connectData[island1][island2] = true;
	_connectData[island2][island1] = true;
}

void Rope::AllDelete()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			_connectData[i][j] = false;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = false;
		}
	}
	_ropeLife = ROPELIFE_NUM;
}

void Rope::Minus(int minus)
{
	if (minus < 0)return;
	_ropeLife -= minus;
	if (_ropeLife < 0) {
		_ropeLife = 0;
	}
}

void Rope::AllRecovery()
{
	_ropeLife = ROPELIFE_NUM;
}

void Rope::Burn(int island1, int island2)
{
	if (island1 < 0 || island1 >= ISLAND_NUM || island2 < 0 || island2 >= ISLAND_NUM)return;
	_fireFlag[island1][island2] = true;
	_fireFlag[island2][island1] = true;
}

bool Rope::GetConnectData(int island1, int island2)
{
	if (island1 < 0 || island1 >= ISLAND_NUM || island2 < 0 || island2 >= ISLAND_NUM)return false;
	if (_connectData[island1][island2] || _connectData[island2][island1]) {
		return true;
	}
	return false;
}

bool Rope::GetFireFlag(int island1, int island2)
{
	if (island1 < 0 || island1 >= ISLAND_NUM || island2 < 0 || island2 >= ISLAND_NUM)return false;
	if (_fireFlag[island1][island2] || _fireFlag[island2][island1]) {
		return true;
	}
	return false;
}

int Rope::GetRopeLife()
{
	return _ropeLife;
}
