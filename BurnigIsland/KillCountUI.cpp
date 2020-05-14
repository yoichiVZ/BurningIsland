#include <DxLib.h>

#include "KillCountUI.h"

KillCountUI::KillCountUI()
{
	_speed = 1;
	Init();
}

void KillCountUI::Init()
{
	_posX = 0;
	_posY = 0;
	_activeFlag = false;
	_liveTime = 0;
}

void KillCountUI::Update()
{
	if (!_activeFlag)return;
	_posY -= _speed;
	_liveTime++;
	if (_liveTime > 60) {
		Init();
	}
}

void KillCountUI::Draw()
{
	DrawFormatString(_posX - 30, _posY - 20, GetColor(0, 0, 0), "%dKILL!!", _killCount);
}

void KillCountUI::SetActive(int posX, int posY, int killCount)
{
	_posX = posX;
	_posY = posY;
	_killCount = killCount;
	_activeFlag = true;
}

bool KillCountUI::GetActiveFlag()
{
	return _activeFlag;
}
