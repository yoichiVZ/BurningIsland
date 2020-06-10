#include <DxLib.h>
#include "RopeLifeDownEfect.h"

#include "MyDrawTurn.h"

RopeLifeDownEfect::RopeLifeDownEfect()
{
	_gh_efect = LoadGraph("Resource\\Image\\Efect01.png");
	GetGraphSize(_gh_efect, &_width, &_height);
	Init();
}

void RopeLifeDownEfect::Init()
{
	_activeFlag = false;

	_posX = _posY = 0;

	_paramVol = 255;

	_frameCount = 0;
}

void RopeLifeDownEfect::Update()
{
	if (!_activeFlag)return;

	_frameCount++;

	_paramVol -= 2;

	if (_paramVol <= 0)Init();
}

void RopeLifeDownEfect::Draw()
{
	if (!_activeFlag)return;

	MyDrawTurn::Instance().SetDrawBrightItem(_posX - _width / 4, _posY - _height / 4, _gh_efect, 0.84f, 255, 255, 255, 
		BLENDMODE_ADD, _paramVol, DRAWTYPE_DRAWEXTENDGRAPH,0,_posX + _width / 4,_posY + _height / 4);
	MyDrawTurn::Instance().SetDrawBrightItem(_posX - _width / 3, _posY - _height / 3, _gh_efect, 0.84f, 0, 255, 0,
		BLENDMODE_ADD, _paramVol, DRAWTYPE_DRAWEXTENDGRAPH, 0, _posX + _width / 3, _posY + _height / 3);
}

void RopeLifeDownEfect::SetEffect(float x, float y)
{
	_activeFlag = true;

	_posX = x;
	_posY = y;
}

bool RopeLifeDownEfect::GetActiveFlag()
{
	return _activeFlag;
}
