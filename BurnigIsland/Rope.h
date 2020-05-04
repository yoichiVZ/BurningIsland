#pragma once
#include "Island.h"
#include "IslandInfo.h"

class Rope {
private:
	int _connectFlag[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _fireCount[IslandInfo::Island_Num][IslandInfo::Island_Num];
	bool _fireFlag[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _fireStartCount[IslandInfo::Island_Num][IslandInfo::Island_Num];
	bool _fireStartFlag[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _maxRopeLife;
	int _ropeLife;

public:
	double _posX[IslandInfo::Island_Num][IslandInfo::Island_Num];
	double _posY[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _moveCount[IslandInfo::Island_Num][IslandInfo::Island_Num];

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
	// ロープを繋げ終わった。
	void ConnectFinished(int island1, int island2);
	// ロープ全消去
	void AllDelete();
	// ロープ消費
	void Minus();
	// ロープ全回復
	void AllRecovery();
	// ロープ回復
	void Recovery();
	// ロープ最大値UP
	void AddMaxLife();
	// 着火
	void Ignition(int island1, int island2);
	// ロープを燃やす
	void Burn(int island1, int island2);

	// 以下 Get関数

	// 繋がっているか
	int GetConnectFlag(int island1, int island2);
	// 燃えているか
	bool GetFireFlag(int island1, int island2);
	// 燃え始めているか
	bool GetFireStartFlag(int island1, int island2);
	// ロープライフ取得
	int GetRopeLife();
};