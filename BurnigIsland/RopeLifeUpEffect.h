#pragma once

#define CHILDPARRICLE_NUM 120

class RopeLifeUpEffect {
private:
	double _posX, _posY;

	double _startPosX, _startPosY;
	double _aimPosX, _aimPosY;
	double _relayPosX1, _relayPosY1;
	double _relayPosX2, _relayPosY2;

	int _greenAlpha;

	int _width, _height;
	bool _activeFlag;
	int _waitingFlag;
	int _deleteFlag;

	double P01[2], P12[2], P23[2];
	double P02[2], P13[2];
	double P03[2];

	double u;
	int _posCounter;
	int _divNum;

	int _childParticleCount;

	int _gh_rightEfect01;

	struct ChildParticle {
		int _posX, _posY;
		int _width, _height;
		int _widthOffset, _heightOffset;
		int _greenAlpha;
		int _alphaSpeed;
		bool _activeFlag;

		int _gh_rightEfect01;

		ChildParticle();
		void Init();
		void Update();
		void Draw();
		void SetActive(int px, int py);
		int GetActiveFlag();
	};

	ChildParticle* _childParticle[CHILDPARRICLE_NUM];

public:
	RopeLifeUpEffect();
	~RopeLifeUpEffect();
	void Init();
	void SetEffect(int x1, int y1, int x2, int y2);
	void Update();
	void Draw();

	void WaitingFlagOf();

	bool GetActiveFlag();

private:
	void BezierCalc();
	void WaitingFlagOn();
};