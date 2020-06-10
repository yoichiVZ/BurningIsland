#include <DxLib.h>
#include "RopeLifeUpEffect.h"

#include "MyDrawTurn.h"

RopeLifeUpEffect::RopeLifeUpEffect()
{
	_gh_rightEfect01 = LoadGraph("Resource\\Image\\Efect01.png");
	GetGraphSize(_gh_rightEfect01, &_width, &_height);
	for (int i = 0; i < CHILDPARRICLE_NUM; i++) {
		_childParticle[i] = new ChildParticle();
	}
	Init();
}

RopeLifeUpEffect::~RopeLifeUpEffect()
{
	for (int i = 0; i < CHILDPARRICLE_NUM; i++) {
		delete _childParticle[i];
	}
}

void RopeLifeUpEffect::Init()
{
	_startPosX = 0;
	_startPosY = 0;
	_aimPosX = 0;
	_aimPosY = 0;
	_relayPosX1 = 0;
	_relayPosY1 = 0;
	_relayPosX2 = 0;
	_relayPosY2 = 0;
	_activeFlag = 0;
	_waitingFlag = 0;
	_deleteFlag = 0;
	_posCounter = 0;
	_divNum = 60;
	_childParticleCount = 0;
	_greenAlpha = 255;
	for (int i = 0; i < CHILDPARRICLE_NUM; i++) {
		_childParticle[i]->Init();
	}
}

void RopeLifeUpEffect::SetEffect(int x1, int y1, int x2, int y2)
{
	_startPosX = x1;
	_startPosY = y1;
	_aimPosX = x2;
	_aimPosY = y2;

	int direction = GetRand(1);
	_relayPosX1 = (direction != 1) ? x1 + (GetRand(250) - 300) : x1 + (GetRand(250) + 50);
	_relayPosY1 = y1 - (GetRand(50) + 50);
	_relayPosX2 = (direction != 1) ? x1 + (GetRand(30) - 50) : x1 + (GetRand(30) + 20);
	_relayPosY2 = y1 + (GetRand(100) + 100);

	_activeFlag = 1;
}

void RopeLifeUpEffect::Update()
{
	if (_deleteFlag == 1) {
		_greenAlpha -= 3;
		if (_greenAlpha < 0)Init();
	}
	if (_waitingFlag == 0) BezierCalc();
	if (_posY > _aimPosY) WaitingFlagOn();

	_childParticleCount++;
	if (_childParticleCount > 2 && _deleteFlag == 0) {
		_childParticleCount = 0;
		for (int i = 0; i < CHILDPARRICLE_NUM; i++) {
			if (_childParticle[i]->GetActiveFlag())continue;
			_childParticle[i]->SetActive(_posX, _posY);
			break;
		}
	}
	for (int i = 0; i < CHILDPARRICLE_NUM; i++) {
		if (!_childParticle[i]->GetActiveFlag())continue;
		_childParticle[i]->Update();
	}
}

void RopeLifeUpEffect::Draw()
{
	MyDrawTurn::Instance().SetDrawBrightItem(_posX - _width / 3, _posY - _height / 3, _gh_rightEfect01, 0.84f, _greenAlpha - 130, _greenAlpha, _greenAlpha - 130, BLENDMODE_ADD, 255,DRAWTYPE_DRAWEXTENDGRAPH,0,_posX + _width / 3,_posY + _height / 3);
	for (int i = 0; i < CHILDPARRICLE_NUM; i++) {
		if (!_childParticle[i]->GetActiveFlag())continue;
		_childParticle[i]->Draw();
	}
}

void RopeLifeUpEffect::WaitingFlagOf()
{
	_deleteFlag = 1;
}

bool RopeLifeUpEffect::GetActiveFlag()
{
	return _activeFlag;
}

void RopeLifeUpEffect::BezierCalc()
{
	_posCounter++;
	u = (1.0 / _divNum) * _posCounter;

	P01[0] = (1.0 - u) * _startPosX + u * _relayPosX1;   P01[1] = (1.0 - u) * _startPosY + u * _relayPosY1;
	P12[0] = (1.0 - u) * _relayPosX1 + u * _relayPosX2;   P12[1] = (1.0 - u) * _relayPosY1 + u * _relayPosY2;
	P23[0] = (1.0 - u) * _relayPosX2 + u * _aimPosX;   P23[1] = (1.0 - u) * _relayPosY2 + u * _aimPosY;

	P02[0] = (1.0 - u) * P01[0] + u * P12[0];   P02[1] = (1.0 - u) * P01[1] + u * P12[1];
	P13[0] = (1.0 - u) * P12[0] + u * P23[0];   P13[1] = (1.0 - u) * P12[1] + u * P23[1];

	P03[0] = (1.0 - u) * P02[0] + u * P13[0]; P03[1] = (1.0 - u) * P02[1] + u * P13[1];

	_posX = P03[0];
	_posY = P03[1];
}

void RopeLifeUpEffect::WaitingFlagOn()
{
	_waitingFlag = 1;
	_posY = _aimPosY;
	_posX = _aimPosX;
}

RopeLifeUpEffect::ChildParticle::ChildParticle()
{
	_gh_rightEfect01 = LoadGraph("Resource\\Image\\Efect01.png");
	GetGraphSize(_gh_rightEfect01, &_width, &_height);
	_width /= 10;
	_height /= 10;
	Init();
}

void RopeLifeUpEffect::ChildParticle::Init()
{
	_posX = 0;
	_posY = 0;
	_widthOffset = 0;
	_heightOffset = 0;
	_greenAlpha = 0;
	_activeFlag = 0;
	_alphaSpeed = 0;
}

void RopeLifeUpEffect::ChildParticle::Update()
{
	_greenAlpha -= _alphaSpeed;
	if (_greenAlpha < 0)Init();
}

void RopeLifeUpEffect::ChildParticle::Draw()
{
	MyDrawTurn::Instance().SetDrawBrightItem(_posX - ((_width / 2) + _widthOffset), _posY - ((_height / 2) + _heightOffset), _gh_rightEfect01, 0.82f, _greenAlpha - 100, _greenAlpha, _greenAlpha - 100, BLENDMODE_ADD, 255,DRAWTYPE_DRAWEXTENDGRAPH,0, _posX + ((_width / 2) + _widthOffset), _posY + ((_height / 2) + _heightOffset));
	//MyDrawTurn::Instance().SetDrawBrightItem(_posX - ((_width / 2)), _posY - ((_height / 2)), _gh_rightEfect01, 0.82f, _greenAlpha - 100, _greenAlpha, _greenAlpha - 100, BLENDMODE_ADD, 255, DRAWTYPE_DRAWEXTENDGRAPH, 0, _posX + ((_width / 2)), _posY + ((_height / 2)));

}

void RopeLifeUpEffect::ChildParticle::SetActive(int px, int py)
{
	_activeFlag = 1;
	_posX = px + (GetRand(40) - 20);
	SRand(GetNowCount());
	_posY = py + (GetRand(40) - 20);
	_widthOffset = _heightOffset = GetRand(5);
	_greenAlpha = 255;
	_alphaSpeed = GetRand(5) + 5;
}

int RopeLifeUpEffect::ChildParticle::GetActiveFlag()
{
	return _activeFlag;
}
