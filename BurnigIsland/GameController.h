#pragma once

#include "Island.h"
#include "Player.h"
#include "Rope.h"
#include "Enemy.h"
#include "Time.h"
#include "Bullet.h"

#include "IslandInfo.h"
#include "EnemyInfo.h"
#include "BulletInfo.h"

//#define ISLAND_NUM 33
#define M_PI 3.14159265358979323846
#define FIRE_RELOAD_NUM 300

class GameController {
private:
	int _mouse_Left, _mousePosX_Left, _mousePosY_Left, _mouseCount_Left;
	int _mouse_Right, _mousePosX_Right, _mousePosY_Right, _mouseCount_Right;
	int _spaceKeyCount;
	int _fireReloadCount;
	bool _fireReloadFlag;
	int _enemyResponCount;
	bool _enemyResponFlag;
	int _killCount;
	int _totalKillCount;
	int _wave;
	int _remainingEnemyCount;

	int _gh_background;
	int _gh_cloud;
	int _background_width, _background_height;
	int _cloud_posX, _cloud_posY;
	int _cloud_width, _cloud_height;

	Island* _island[IslandInfo::Island_Num];
	Player _player;
	Rope _rope;
	Enemy* _enemy[EnemyInfo::Enemy_Num];
	Time _time;
	Bullet* _bullet[BulletInfo::Bullet_Num];

	enum Scenetate {
		TITLE,
		TUTORIAL,
		GAMEPLAY,
		RESULT
	};
	Scenetate _sceneState;

public:
	GameController();
	~GameController();
	void Init();
	void All();

private:
	void Title();
	void Tutorial();
	void GamePlay();
	void Result();
	void Draw();
	int OnMouseButtonLeft();
	int OnMouseButtonRight();
	int OnSpaceButton();
	int LengthCheck(int posX1, int posY1, int posX2, int posY2);
	void EnemySpawn(Enemy* enemy);
};