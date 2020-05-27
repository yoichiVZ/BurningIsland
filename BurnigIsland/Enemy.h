#pragma once
#include "Bullet.h"

//#define ENEMY_ROTATE 10
//#define ENEMY_NUM 30
//#define ENEMY_RANGE 200
#define ENEMYTYPE_SLIME 0
#define ENEMYTYPE_MONKEY 1
#define ENEMYTYPE_DEMON 2

class Enemy {
private:
	int _firstPosX, _firstPosY;
	int _posX, _posY;
	int _jumpPosX, _jumpPosY;
	double _jumpVecX, _jumpVecY;
	double _jumpVPosX, _jumpVPosY;
	double _vertualPosX, _vertualPosY;
	double _deletePosX, _deletePosY;
	double _speedX, _speedY;
	double _angle;
	int _jumpMoveCount;
	int _jumpFinishCount;
	bool _jumpMoveFlag;
	bool _jumpNowFlag;
	bool _liveFlag;
	bool _dethDelayFlag;
	bool _ropeModeFlag;
	bool _firstMoveFlag;
	bool _perceiveFlag;
	int _ropeMoveCount;
	int _lastTouchIslandNumber;
	int _atackChargeCount;
	int _dethDelayCount;

	int _nextJumpPosX, _nextJumpPosY;
	int _nextJumpIslandNumber;

	int _gh_suraimu;
	int _gh_suraimu_anim_idle[10];
	int _gh_suraimu_anim_jump[18];
	int _gh_suraimu_anim_deth[9];
	int _gh_saru_anim_idle[7];
	int _gh_saru_anim_walk[12];
	int _gh_saru_anim_jump[18];
	int _gh_saru_anim_deth[9];
	int _gh_akuma_anim_idle[7];
	int _gh_akuma_anim_move[6];
	int _gh_akuma_anim_attack[20];
	int _gh_akuma_anim_deth[9];
	int _gh_perceive;
	int _animPos_suraimu_idle;
	int _animPos_suraimu_jump;
	int _animPos_suraimu_deth;
	int _animPos_saru_idle;
	int _animPos_saru_walk;
	int _animPos_saru_jump;
	int _animPos_saru_deth;
	int _animPos_akuma_idle;
	int _animPos_akuma_move;
	int _animPos_akuma_attack;
	int _animPos_akuma_attackDelay;
	int _animPos_akuma_deth;
	int _animCount_suraimu_idle;
	int _animCount_suraimu_jump;
	int _animCount_suraimu_deth;
	int _animCount_saru_idle;
	int _animCount_saru_walk;
	int _animCount_saru_jump;
	int _animCount_saru_deth;
	int _animCount_akuma_idle;
	int _animCount_akuma_move;
	int _animCount_akuma_attack;
	int _animCount_akuma_attackDelay;
	int _animCount_akuma_deth;
	int _animFlag_akuma_attackDelay;
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
	int _onthThinkFlag;
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
	void Instantiate(int px, int py, int dis_number);
	// �����ʒu�Z�b�g
	void SetFirstPosition(int px, int py);
	// �W�����v�J�n
	void JumpStart(int posX, int posY);
	// �W�����v�ړ�
	void JumpMove();
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
	void SetPerceiveFlag(bool perceiveFlag);
	void SetNextJumpInfo(int px, int py, int islandNum);

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
	bool GetJumpNowFlag();
	int GetJumpPosX();
	int GetJumpPosY();
	int GetNextJumpPosX();
	int GetNextJumpPosY();
	int GetNextJumpIslandNumber();
	int GetFirstMoveFlag();

private:
	// ���[�v�ړ�
	void RopeMove();
	// �������[�u
	void FirstMove();
};