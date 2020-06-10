#include "WaveUpEffect.h"
#include <DxLib.h>
#include "MyDrawTurn.h"

#include "WindowInfo.h"

WaveUpEffect::WaveUpEffect()
{
	_gh_wave = LoadGraph("Resource\\Image\\WAVE.png");
	GetGraphSize(_gh_wave, &_width_wave, &_height_wave);
	_gh_waveUp = LoadGraph("Resource\\Image\\WAVE2.png");
	GetGraphSize(_gh_waveUp, &_width_waveUp, &_height_waveUp);
	Init();
}

void WaveUpEffect::Init()
{
	_activeFlag = false;

	_posX = 10;
	_posY = 20;

	_speed_fast = 30;
	_speed_slow = 2;
	_speedFlag = FALSE;
	_moveFlag1 = _moveFlag2 = _moveFlag3 = FALSE;
}

void WaveUpEffect::Update()
{
	if (!_activeFlag)return;

	if (_moveFlag1) {
		_posX += _speed_fast;
		if (_posX >= WindowInfo::Screen_Width) {
			_moveFlag1 = false;
			_moveFlag2 = true;
			_posY = 250;
		}
	}
	if (_moveFlag2) {
		if (!_speedFlag) {
			_posX -= _speed_fast;
			if (_posX < WindowInfo::Screen_Width / 2 - 200 && _posX > WindowInfo::Screen_Width / 2 - 350) {
				_speedFlag = true;
			}
			if (_posX + _width_waveUp + 10 + 100 < 0) {
				_moveFlag2 = false;
				_moveFlag3 = true;
				_posX = 0 - _width_wave + 10 + 40;
				_posY = 20;
			}
		}
		else {
			_posX -= _speed_slow;
			if (_posX < WindowInfo::Screen_Width / 2 - 350) {
				_speedFlag = false;
			}
		}
	}
	if (_moveFlag3) {
		_posX += _speed_fast;
		if (_posX >= 10) {
			_moveFlag3 = false;
			//_posX = 10;
			_activeFlag = false;
		}
	}
}

void WaveUpEffect::Draw()
{
	if (!_activeFlag)return;
	if (_moveFlag1 || _moveFlag3) {
		MyDrawTurn::Instance().SetDrawItem(_posX, _posY, _gh_wave, 0.8f);
		_drawNumber.Draw(_posX + _width_wave + 10, _posY - 10, _wave, SETDRAWNUM_WAVE);
	}
	if (_moveFlag2) {
		MyDrawTurn::Instance().SetDrawItem(_posX, _posY, _gh_waveUp, 0.8f);
		_drawNumber.Draw(_posX + _width_waveUp + 10, _posY, _wave, SETDRAWNUM_WAVEUP);
	}
}

void WaveUpEffect::Instantiate(int wave)
{
	_activeFlag = true;
	_posX = 10;
	_posY = 20;
	_wave = wave;
	_moveFlag1 = true;
}

bool WaveUpEffect::GetActiveFlag()
{
	return _activeFlag;
}
