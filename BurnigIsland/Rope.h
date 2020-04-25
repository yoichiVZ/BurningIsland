#pragma once
#include "Island.h"

#define ROPELIFE_NUM 800

class Rope {
public:
	int _connectDate[ISLAND_NUM][ISLAND_NUM];
	int _fireCount[ISLAND_NUM][ISLAND_NUM];
	bool _fireFlag[ISLAND_NUM][ISLAND_NUM];
	int _ropeLife;

	Rope();
	~Rope();
	void Init();
	void Update();
	void Draw();
	void All();
	void Instantiate(Island* island_1, Island* island_2);
	void Connect(int island_1, int island_2);
	void AllDelete();
};