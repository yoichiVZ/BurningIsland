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

	// ����֐�

	// ���_�Ɠ������Ă��邩
	bool BaseHitCheck();

	// Get�֐�

	// �����Ă��邩
	bool GetLiveFlag();

private:
	void Move();
};