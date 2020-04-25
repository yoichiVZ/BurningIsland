#pragma once

#define PLAYER_ROTATE 10
#define ROPE_DISTANSE 10

class Player {
private:
	int _posX, _posY;
	int _rotation;
	int _hp;

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
	void All();
	// ダメージ
	void Damage();
	// 移動
	void Move(int posX, int posY);

	// 以下 Get関数

	// X座標取得
	int GetPosX();
	// Y座標取得
	int GetPosY();
	// HP取得
	int GetHP();
	// 生死状態取得
	bool GetLive();
};