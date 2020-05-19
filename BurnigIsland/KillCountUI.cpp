#include <DxLib.h>

#include "KillCountUI.h"
#include "MyDrawTurn.h"

KillCountUI::KillCountUI()
{
	_gh_burning = LoadGraph("Resource\\Image\\BURNING.png");
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
	_posY -= _speed;
	_liveTime++;
	if (_liveTime > 60) {
		Init();
	}
}

void KillCountUI::Draw()
{
	//DrawFormatString(_posX - 30, _posY - 20, GetColor(0, 0, 0), "%dBurnig!!", _killCount);
	drawNumber.Draw(_posX - 80, _posY - 35, _killCount, SETDRAWNUM_KILLCOUNT);
	MyDrawTurn::Instance().SetDrawItem(_posX - 60, _posY - 30, _gh_burning, 0.8f);
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
