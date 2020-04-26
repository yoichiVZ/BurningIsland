#pragma once
#include "Island.h"
#include "Player.h"
#include "Rope.h"
#include "Enemy.h"
#include "Time.h"

//#define ISLAND_NUM 33
#define M_PI 3.14159265358979323846

class GameController {
private:
	int _mouse_Left, _mousePosX_Left, _mousePosY_Left, _mouseCount_Left;
	int _mouse_Right, _mousePosX_Right, _mousePosY_Right, _mouseCount_Right;
	int _fireReloadCount;
	bool _fireReloadFlag;
	int _enemyResponCount;
	bool _enemyResponFlag;

	Island* _island[ISLAND_NUM];
	Player _player;
	Rope _rope;
	Enemy* _enemy[ENEMY_NUM];
	Time _time;

public:

	GameController();
	~GameController();
	void Init();
	void Title();
	void GamePlay();
	void Result();
	void Draw();
	void All();
	int OnMouseButtonLeft();
	int OnMouseButtonRight();
	int LengthCheck(int posX1, int posY1, int posX2, int posY2);
	void EnemySpawn(Enemy* enemy);
};