#pragma once

#define YUGUDORASIRU_PARITCLE_NUM 10

class YugudorasiruParticle {
private:
	float _posX, _posY;
	int _width, _height;
	int _width_offset;
	int _height_offset;
	double _angle;
	double _movementAngle;
	float _speed;
	int _greenBright;
	int _brightDistance;
	int _deleteSpeed;
	bool _activeFlag;

	int _gh_rightEfect01;
	int _gh_rightEfect02;

public:
	YugudorasiruParticle();
	void Init();
	void SetActive(float posX, float posY);
	void Move();
	void Draw();
	bool GetActive();
};