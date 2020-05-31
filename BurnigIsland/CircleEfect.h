#pragma once
#include "Vector2D.h"

#define CIRCLEEFECT_CHILDNUM 10

class CircleEfect {
private:
	bool		_activeFlag;

	int			_frameCount;

public:
	Vector2D	_centerPos;
	double		_centerAngle;
	// 初期値1
	double		_centerAngleChangeVol;
	int			_centerRotate;
	// 初期値0
	int			_centerRotateChangeVol;

	Vector2D	_childPos[CIRCLEEFECT_CHILDNUM];
	int			_childRotate[CIRCLEEFECT_CHILDNUM];
	// 初期値5
	int			_childRotateChangeVol;

	// 初期値255
	int			_colorR, _colorG, _colorB;

	// 初期値255
	int			_param;
	// 初期値5
	int			_paramChangeVol;

	int			_blendState;

	CircleEfect();
	void Init();
	void Update();
	void Draw();
	void SetCircleEfect(Vector2D pos);
};