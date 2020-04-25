#pragma once

#define PLAYER_ROTATE 10
#define ROPE_DISTANSE 10

class Player {
public:
	int _posX, _posY;
	int _rotation;
	int _hp;

	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
	void All();
	void Damage();
};