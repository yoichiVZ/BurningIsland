#pragma once

#define SHIELDBREAKEFFECT_NUM 100

class ShieldBreakEffect {
private:
	bool _activeFlag;

	int _posX, _posY;
	int _width, _height;

	int _vecX, _vecY;
	int _gravity;

	int _gh;

	int _frameCount;
public:
	ShieldBreakEffect();
	void Init();
	void Update();
	void Draw();
	void Instantiate(int px, int py);
	bool GetActiveFlag();
	//void SetActive(bool activeFlag);
};