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
	// 死亡
	void Deth();
	// 焼死
	void Deth_Fire();
	// 生成
	void Instantiate(int px, int py, int dis_number);
	// 初期位置セット
	void SetFirstPosition(int px, int py);
	// ジャンプ開始
	void JumpStart(int posX, int posY);
	// ジャンプ移動
	void JumpMove();
	// スピードセット
	void SetSpeed(double speedX, double speedY);
	// angleセット
	void SetAngle(double angle);
	// 一つ前にいた島番号としてセット
	void SetLastTouchIslandNumber(int lastTouchIslandNumber);
	// ジャンプフラグをfalseに
	void OffJumpMoveFlag();
	// ロープに乗る
	void OnRopeModeFlag();
	// ロープから降りる
	void OffRopeModeFlag();
	// 弾を撃つ
	void Shot(Bullet* bullet,int targetPosX, int targetPosY);
	// 攻撃
	void Attack();
	void SetPerceiveFlag(bool perceiveFlag);
	void SetNextJumpInfo(int px, int py, int islandNum);

	// 判定関数

	// 射程距離内に拠点があるか
	bool RangeCheck();

	// Get関数

	// X座標取得
	int GetPosX();
	// Y座標取得
	int GetPosY();
	// 一つ前にいた島番号取得
	int GetLastTouchIslandNumber();
	// angle取得
	double GetAngle();
	// ロープに乗っているか
	bool GetRopeModeFlag();
	// 生きているか
	bool GetLiveFlag();
	// 焼死中か
	bool GetDethDelayFlag();
	// ジャンプ可能か
	bool GetJumpMoveFlag();
	bool GetJumpNowFlag();
	int GetJumpPosX();
	int GetJumpPosY();
	int GetNextJumpPosX();
	int GetNextJumpPosY();
	int GetNextJumpIslandNumber();
	int GetFirstMoveFlag();

private:
	// ロープ移動
	void RopeMove();
	// 初期ムーブ
	void FirstMove();
};