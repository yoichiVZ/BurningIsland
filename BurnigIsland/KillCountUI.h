#pragma once

class KillCountUI {
private:
	int _posX, _posY;
	int _speed;
	bool _activeFlag;
	int _killCount;
	int _liveTime;

public:
	KillCountUI();
	void Init();
	void Update();
	void Draw();
	void SetActive(int posX, int posY, int killCount);
	bool GetActiveFlag();
};