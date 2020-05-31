#include <DxLib.h>
#include "CircleEfect.h"

CircleEfect::CircleEfect()
{
	Init();
}

void CircleEfect::Init()
{
	_activeFlag = false;

	_frameCount = 0;

	_centerPos = Vector2D();
	_centerAngle = 0;
	_centerAngleChangeVol = 1;
	_centerRotate = 100;
	_centerRotateChangeVol = 0;

	for (int i = 0; i < CIRCLEEFECT_CHILDNUM; i++) {
		auto angle = _centerAngle + ((360 / CIRCLEEFECT_CHILDNUM * i) * (3.14159265358979323846 / 180));
		auto testx = cos(angle) * _centerRotate;
		auto testy = sin(angle) * _centerRotate;
		_childPos[i] = Vector2D(_centerPos.x + (cos(angle) * _centerRotate), _centerPos.y + (sin(angle) * _centerRotate));
		_childRotate[i] = 50;
	}
	_childRotateChangeVol = 5;

	_colorR = _colorG = _colorB = 255;

	_param = 255;
	_paramChangeVol = 5;

	_blendState = DX_BLENDMODE_NOBLEND;
}

void CircleEfect::Update()
{
	if (!_activeFlag)return;

	if (_param < 0)Init();

	_frameCount++;
	if (_frameCount % 2 != 0)return;
	
	_param -= _paramChangeVol;

	_centerAngle += _centerAngleChangeVol * 180 / 3.14159265358979323846;
	_centerRotate += _centerRotateChangeVol;


	for (int i = 0; i < CIRCLEEFECT_CHILDNUM; i++) {
		auto angle = _centerAngle + ((360 / CIRCLEEFECT_CHILDNUM * i) * (3.14159265358979323846 / 180));
		_childPos[i] = Vector2D(_centerPos.x + (cos(angle) * _centerRotate), _centerPos.y + (sin(angle) * _centerRotate));
		_childRotate[i] += _childRotateChangeVol;
	}
}

void CircleEfect::Draw()
{
	if (!_activeFlag)return;

	switch (_blendState) {
	case DX_BLENDMODE_NOBLEND:
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case DX_BLENDMODE_ALPHA:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _param);
		break;
	case DX_BLENDMODE_ADD:
		SetDrawBlendMode(DX_BLENDMODE_ADD, _param);
		break;
	default:
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}

	for (int i = 0; i < CIRCLEEFECT_CHILDNUM; i++) {
		DrawCircle(_childPos[i].x, _childPos[i].y, _childRotate[i], GetColor(_colorR, _colorG, _colorB), FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void CircleEfect::SetCircleEfect(Vector2D pos)
{
	_activeFlag = true;

	_centerPos = pos;
}
