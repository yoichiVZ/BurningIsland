#pragma once

class RopeLifeDownEfect {
private:
	bool _activeFlag;

	float _posX, _posY;
	int _width, _height;

	int _gh_efect;

	int _paramVol;
	
	int _frameCount;

public:
	RopeLifeDownEfect();
	void Init();
	void Update();
	void Draw();
	void SetEffect(float x, float y);
	bool GetActiveFlag();
};