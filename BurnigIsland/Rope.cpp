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
			_connectDate[i][j] = 0;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = false;
		}
	}
	_ropeLife = ROPELIFE_NUM;
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
				_connectDate[i][j] = 0;
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

void Rope::Instantiate(Island* island_1, Island* island_2)
{
}

void Rope::Connect(int island_1, int island_2)
{
	_connectDate[island_1][island_2] = 1;
}

void Rope::AllDelete()
{
	for (int i = 0; i < ISLAND_NUM; i++) {
		for (int j = 0; j < ISLAND_NUM; j++) {
			_connectDate[i][j] = 0;
			_fireCount[i][j] = 0;
			_fireFlag[i][j] = false;
		}
	}
	_ropeLife = ROPELIFE_NUM;
}