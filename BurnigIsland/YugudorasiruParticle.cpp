#include <DxLib.h>
#include <math.h>
#include "YugudorasiruParticle.h"

#include "MyDrawTurn.h"

#define PI 3.14159265358979323846

YugudorasiruParticle::YugudorasiruParticle()
{
	_gh_rightEfect01 = LoadGraph("Resource\\Image\\Efect01.png");
	_gh_rightEfect02 = LoadGraph("Resource\\Image\\Efect02.png");
	GetGraphSize(_gh_rightEfect01, &_width, &_height);
	_width /= 10;
	_height /= 10;
	Init();
}

void YugudorasiruParticle::Init()
{
	_posX = _posY = 0;
	_angle = GetRand(360) * PI / 180;
	_movementAngle = (GetRand(10) - 5) * PI / 180;
	_speed = 0.5;
	_activeFlag = false;
	_greenBright = 255;
	_brightDistance = 100;
	_width_offset = _height_offset = GetRand(10) - 5;
	_deleteSpeed = GetRand(2) + 1;
}

void YugudorasiruParticle::SetActive(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
	_activeFlag = true;
}

void YugudorasiruParticle::Move()
{
	_posX += cos(_angle) * _speed;
	_posY += sin(_angle) * _speed;

	_angle += _movementAngle;
	_movementAngle = (GetRand(10) - 5) * PI / 180;
}

void YugudorasiruParticle::Draw()
{
	_greenBright -= _deleteSpeed;
	int size = (_width + _width_offset);
	int minusSize = (_width + _width_offset) * 7 / 10;
	MyDrawTurn::Instance().SetDrawBrightItem(_posX - size, _posY - size, _gh_rightEfect01, 0.82f,
		_greenBright - _brightDistance, _greenBright, _greenBright - _brightDistance,
		BLENDMODE_ADD, 180, DRAWTYPE_DRAWEXTENDGRAPH, 0, _posX + size, _posY + size);
	MyDrawTurn::Instance().SetDrawBrightItem(_posX - minusSize, _posY - minusSize, _gh_rightEfect02, 0.82f,
		_greenBright - _brightDistance, _greenBright, _greenBright - _brightDistance,
		BLENDMODE_ADD, 180, DRAWTYPE_DRAWEXTENDGRAPH, 0, _posX + minusSize, _posY + minusSize);

	if (_greenBright <= 0) {
		Init();
	}
}

bool YugudorasiruParticle::GetActive()
{
	return _activeFlag;
}
