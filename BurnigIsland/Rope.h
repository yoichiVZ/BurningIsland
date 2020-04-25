#pragma once
#include "Island.h"

#define ROPELIFE_NUM 800

class Rope {
private:
	bool _connectFlag[ISLAND_NUM][ISLAND_NUM];
	int _fireCount[ISLAND_NUM][ISLAND_NUM];
	bool _fireFlag[ISLAND_NUM][ISLAND_NUM];
	int _ropeLife;

public:
	Rope();
	~Rope();
	// 初期化
	void Init();
	// 更新
	void Update();
	void Draw();
	void All();
	// ロープを繋げる
	void Connect(int island1, int island2);
	// ロープ全消去
	void AllDelete();
	// ロープ消費
	void Minus(int minus);
	// ロープ全回復
	void AllRecovery();
	// ロープを燃やす
	void Burn(int island1, int island2);

	// 以下 Get関数

	// 繋がっているか
	bool GetConnectFlag(int island1, int island2);
	// 燃えているか
	bool GetFireFlag(int island1, int island2);
	// ロープライフ取得
	int GetRopeLife();
};