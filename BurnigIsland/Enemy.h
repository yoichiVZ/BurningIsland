#pragma once

#define ENEMY_ROTATE 10
#define ENEMY_NUM 10

class Enemy {
public:
	int _firstPosX, _firstPosY;
	int _posX, _posY;
	double _vertualPosX, _vertualPosY;
	double _deletePosX, _deletePosY;
	double _speedX, _speedY;
	double _angle;
	int _moveCount;
	bool _moveFlag;
	bool _liveFlag;
	bool _ropemode;
	int _ropeMoveCount;
	int _lastTouchIsland;

	Enemy();
	Enemy(int posX, int posY);
	~Enemy();
	void Init();
	void Update();
	void Draw();
	void All();
	void Deth();
	void Instantiate(int px, int py);
	void Move();
};