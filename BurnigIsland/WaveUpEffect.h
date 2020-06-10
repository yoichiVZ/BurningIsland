#pragma once
#include "DrawNumber.h"

class WaveUpEffect {
private:
	bool _activeFlag;

	int _posX, _posY;
	int _width_wave, _height_wave;
	int _width_waveUp, _height_waveUp;

	int _speed_fast;
	int _speed_slow;
	
	int _moveFlag1, _moveFlag2, _moveFlag3;
	int _speedFlag;

	int _wave;

	int _gh_wave;
	int _gh_waveUp;

	DrawNumber _drawNumber;

public:
	WaveUpEffect();
	// ‰Šú‰»
	void Init();
	// XVˆ—
	void Update();
	// •`‰æˆ—
	void Draw();
	// ¶¬
	void Instantiate(int wave);

	bool GetActiveFlag();
};