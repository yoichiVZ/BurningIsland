#pragma once
#include "Bullet.h"

//#define ENEMY_ROTATE 10
//#define ENEMY_NUM 30
//#define ENEMY_RANGE 200

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
	bool _dethDelayFlag;
	bool _ropeModeFlag;
	bool _firstMoveFlag;
	int _ropeMoveCount;
	int _lastTouchIslandNumber;
	int _atackChargeCount;
	int _dethDelayCount;

	int _gh_suraimu;
	int _gh_akuma;
	int _gh_saru;
	int _gh_suraimu_deth;
	int _gh_akuma_deth;
	int _gh_saru_deth;
	int _suraimu_width, _suraimu_height;
	int _akuma_width, _akuma_height;
	int _saru_width, _saru_height;

	int _resPosX, _resPosY;

	int _sh_attack_allow;
	int _sh_attack_monkey;
	int _sh_attack_slime;

public:
	int _dis_number;
	bool _atackModeFlag;
	bool _atackChargeflag;
	Enemy();
	Enemy(int posX, int posY);
	~Enemy();
	void Init();
	void Update();
	void Draw();
	void All();
	// ���S
	void Deth();
	// �Ď�
	void Deth_Fire();
	// ����
	void Instantiate(int px, int py);
	// �����ʒu�Z�b�g
	void SetFirstPosition(int px, int py);
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
	// �e������
	void Shot(Bullet* bullet,int targetPosX, int targetPosY);
	// �U��
	void Attack();

	// ����֐�

	// �˒��������ɋ��_�����邩
	bool RangeCheck();

	// Get�֐�

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
	// �Ď�����
	bool GetDethDelayFlag();
	// �W�����v�\��
	bool GetJumpMoveFlag();

private:
	// ���[�v�ړ�
	void RopeMove();
	// �������[�u
	void FirstMove();
};