#include "ShieldBreakEffect.h"
#include <DxLib.h>
#include "WindowInfo.h"
#include "MyDrawTurn.h"

ShieldBreakEffect::ShieldBreakEffect()
{
	_gh = LoadGraph("Resource\\Image\\Baria1.png");
	GetGraphSize(_gh, &_width, &_height);
	Init();
}

void ShieldBreakEffect::Init()
{
	_activeFlag = false;

	_posX = _posY = 0;
	
	_vecX = _vecY = 0;

	_gravity = 2;

	_frameCount = 0;
}

void ShieldBreakEffect::Update()
{
	if (!_activeFlag)return;

	_frameCount++;

	if (_frameCount % 2 == 1)return;

	_vecY += _gravity;

	_posX += _vecX;
	_posY += _vecY;

	if (_posY > WindowInfo::Screen_Height + _height / 2)Init();
}

void ShieldBreakEffect::Draw()
{
	if (!_activeFlag)return;
	MyDrawTurn::Instance().SetDrawItem(_posX, _posY, _gh, 0.8f, DRAWTYPE_DRAWROTAGRAPH, 0.1f);
}

void ShieldBreakEffect::Instantiate(int px, int py)
{
	_posX = px;
	_posY = py;

	_vecX = GetRand(10) - 5;
	_vecY = -(GetRand(15) + 5);

	_activeFlag = true;
}

bool ShieldBreakEffect::GetActiveFlag()
{
	return _activeFlag;
}
