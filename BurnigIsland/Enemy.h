#pragma once

#define ENEMY_ROTATE 10
#define ENEMY_NUM 10

class Enemy {
private:
	int _firstPosX, _firstPosY;
	int _posX, _posY;
	double _vertualPosX, _vertualPosY;
	double _deletePosX, _deletePosY;
	double _speedX, _speedY;
	double _angle;
	int _jumpMoveCount;
	bool _jumpMoveFlag;
	bool _liveFlag;
	bool _ropeModeFlag;
	int _ropeMoveCount;
	int _lastTouchIslandNumber;

public:
	Enemy();
	Enemy(int posX, int posY);
	~Enemy();
	void Init();
	void Update();
	void Draw();
	void All();
	void Deth();
	void Instantiate(int px, int py);
	// ジャンプ移動
	void JumpMove(int posX, int posY);
	// スピードセット
	void SetSpeed(double speedX, double speedY);
	// angleセット
	void SetAngle(double angle);
	// 一つ前にいた島番号としてセット
	void SetLastTouchIslandNumber(int lastTouchIslandNumber);
	// ジャンプフラグをfalseに
	void OffJumpMoveFlag();
	// ロープに乗る
	void OnRopeModeFlag();
	// ロープから降りる
	void OffRopeModeFlag();

	// 以下 Get関数

	// X座標取得
	int GetPosX();
	// Y座標取得
	int GetPosY();
	// 一つ前にいた島番号取得
	int GetLastTouchIslandNumber();
	// angle取得
	double GetAngle();
	// ロープに乗っているか
	bool GetRopeModeFlag();
	// 生きているか
	bool GetLiveFlag();
	// ジャンプ可能か
	bool GetJumpMoveFlag();

private:
	// ロープ移動
	void RopeMove();
};