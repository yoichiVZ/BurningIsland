#pragma once

class Bullet {
private:
	double _posX, _posY;
	double _movementX, _movementY;
	bool _liveFlag;

public:
	Bullet();
	void Init();
	void Update();
	void Draw();
	void All();
	void SetTarget(int posX,int posY,int target_posX,int target_posY);
	void Deth();

	// ”»’èŠÖ”

	// ‹’“_‚Æ“–‚½‚Á‚Ä‚¢‚é‚©
	bool BaseHitCheck();

	// GetŠÖ”

	// ¶‚«‚Ä‚¢‚é‚©
	bool GetLiveFlag();

private:
	void Move();
};