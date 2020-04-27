#pragma once

#define BULLET_NUM 30
#define BULLET_ROTATE 5
#define BULLET_SPEED 5

class Bullet {
private:
	double _posX, _posY;
	double _movementX, _movementY;
	bool _liveFlag;

public:
	Bullet();
	void Init();
	void Update();
	void Draw();
	void All();
	void SetTarget(int posX,int posY,int target_posX,int target_posY);
	void Deth();
private:
	void Move();
};