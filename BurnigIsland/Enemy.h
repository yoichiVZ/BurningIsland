#pragma once

#define ENEMY_ROTATE 10
#define ENEMY_NUM 10

class Enemy {
private:
	int _firstPosX, _firstPosY;
	int _posX, _posY;
	double _vertualPosX, _vertualPosY;
	double _deletePosX, _deletePosY;
	double _speedX, _speedY;
	double _angle;
	int _jumpMoveCount;
	bool _jumpMoveFlag;
	bool _liveFlag;
	bool _ropeModeFlag;
	int _ropeMoveCount;
	int _lastTouchIslandNumber;

public:
	Enemy();
	Enemy(int posX, int posY);
	~Enemy();
	void Init();
	void Update();
	void Draw();
	void All();
	void Deth();
	void Instantiate(int px, int py);
	// �W�����v�ړ�
	void JumpMove(int posX, int posY);
	// �X�s�[�h�Z�b�g
	void SetSpeed(double speedX, double speedY);
	// angle�Z�b�g
	void SetAngle(double angle);
	// ��O�ɂ������ԍ��Ƃ��ăZ�b�g
	void SetLastTouchIslandNumber(int lastTouchIslandNumber);
	// �W�����v�t���O��false��
	void OffJumpMoveFlag();
	// ���[�v�ɏ��
	void OnRopeModeFlag();
	// ���[�v����~���
	void OffRopeModeFlag();

	// �ȉ� Get�֐�

	// X���W�擾
	int GetPosX();
	// Y���W�擾
	int GetPosY();
	// ��O�ɂ������ԍ��擾
	int GetLastTouchIslandNumber();
	// angle�擾
	double GetAngle();
	// ���[�v�ɏ���Ă��邩
	bool GetRopeModeFlag();
	// �����Ă��邩
	bool GetLiveFlag();
	// �W�����v�\��
	bool GetJumpMoveFlag();

private:
	// ���[�v�ړ�
	void RopeMove();
};