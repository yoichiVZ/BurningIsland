#pragma once
#include "DrawNumber.h"

class KillCountUI {
private:
	int _posX, _posY;
	int _speed;
	bool _activeFlag;
	int _killCount;
	int _liveTime;

	int _gh_burning;

	DrawNumber drawNumber;

public:
	KillCountUI();
	void Init();
	void Update();
	void Draw();
	void SetActive(int posX, int posY, int killCount);
	bool GetActiveFlag();
};