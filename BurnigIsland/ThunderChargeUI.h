#pragma once

class ThunderChargeUI {
private:
	int _posX, _posY;
	int _width, _height;
	double _angle;
	double _angleSpeed;
	bool _activeFlag;

	int _gh_thunderChargeUI;
public:
	ThunderChargeUI();
	void Init();
	void Update();
	void Draw();
	void SetActive(bool activeFlag);
};