#include <DxLib.h>
#include "ThunderChargeUI.h"

#include "MyDrawTurn.h"

ThunderChargeUI::ThunderChargeUI()
{
	_gh_thunderChargeUI = LoadGraph("Resource\\Image\\UItya-zi.png");
	GetGraphSize(_gh_thunderChargeUI, &_width, &_height);
	_angleSpeed = (2 * (3.14159265358979323846 / 180));
	Init();
}

void ThunderChargeUI::Init()
{
	_posX = 98;
	_posY = 713;
	_angle = 0;
	_activeFlag = true;
}

void ThunderChargeUI::Update()
{
	if (!_activeFlag)return;
	_angle += _angleSpeed;
}

void ThunderChargeUI::Draw()
{
	if (!_activeFlag)return;
	MyDrawTurn::Instance().SetDrawItem(_posX, _posY, _gh_thunderChargeUI, 0.84f, DRAWTYPE_DRAWROTAGRAPH, 1.1, _angle,BLENDMODE_ALPHA,255);
}

void ThunderChargeUI::SetActive(bool activeFlag)
{
	if (activeFlag) {
		_activeFlag = true;
		return;
	}
	_activeFlag = false;
}
