#include "DxLib.h"
#include "Enemy.h"

#include "IslandInfo.h"
#include "EnemyInfo.h"

#include "MyDrawTurn.h"

//#include "Island.h"

Enemy::Enemy()
{
	_gh_suraimu = LoadGraph("Resource\\Image\\suraimu.png");
	LoadDivGraph("Resource\\Image\\SuraimuAnime.png", 10, 5, 2, 60, 60, _gh_suraimu_anim_idle);
	LoadDivGraph("Resource\\Image\\SuraimuJumpAnime.png", 18, 5, 4, 60, 60, _gh_suraimu_anim_jump);
	LoadDivGraph("Resource\\Image\\MoeruSuraimu.png", 9, 3, 3, 60, 60, _gh_suraimu_anim_deth);
	LoadDivGraph("Resource\\Image\\SaruStand.png", 7, 4, 2, 100, 100, _gh_saru_anim_idle);
	LoadDivGraph("Resource\\Image\\SaruIdou.png", 12, 4, 3, 100, 100, _gh_saru_anim_walk);
	LoadDivGraph("Resource\\Image\\SaruJamp.png", 18, 5, 4, 100, 140, _gh_saru_anim_jump);
	LoadDivGraph("Resource\\Image\\MoeruSaru.png", 9, 3, 3, 100, 100, _gh_saru_anim_deth);
	LoadDivGraph("Resource\\Image\\AkumaStand.png", 7, 3, 3, 70, 70, _gh_akuma_anim_idle);
	LoadDivGraph("Resource\\Image\\AkumaIdou.png", 6, 3, 2, 70, 70, _gh_akuma_anim_move);
	LoadDivGraph("Resource\\Image\\AkumaShot.png", 20, 5, 4, 70, 70, _gh_akuma_anim_attack);
	LoadDivGraph("Resource\\Image\\MoeruAkuma.png", 9, 3, 3, 70, 70, _gh_akuma_anim_deth);
	_gh_perceive = LoadGraph("Resource\\Image\\!.png");
	_gh_akuma = LoadGraph("Resource\\Image\\akuma.png");
	_gh_saru = LoadGraph("Resource\\Image\\saru.png");
	_gh_suraimu_deth = LoadGraph("Resource\\Image\\suraimuD.png");
	_gh_akuma_deth = LoadGraph("Resource\\Image\\akumaD.png");
	_gh_saru_deth = LoadGraph("Resource\\Image\\saruD.png");
	GetGraphSize(_gh_suraimu_anim_idle[0], &_suraimu_width, &_suraimu_height);
	GetGraphSize(_gh_saru_anim_idle[0], &_saru_width, &_saru_height);
	GetGraphSize(_gh_akuma_anim_idle[0], &_akuma_width, &_akuma_height);
	_sh_attack_allow = LoadSoundMem("Resource\\Sound\\enemyattack_allow.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_attack_allow);
	_sh_attack_monkey = LoadSoundMem("Resource\\Sound\\enemyattack_monkey.mp3");
	ChangeVolumeSoundMem(255 * 40 / 100, _sh_attack_monkey);
	_sh_attack_slime = LoadSoundMem("Resource\\Sound\\enemyattack_slime.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, _sh_attack_slime);
	_atackModeFlag = false;
	Init();
}

Enemy::Enemy(int posX, int posY)
{
	_firstPosX = posX;
	_firstPosY = posY;
	Init();
	_liveFlag = false;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	_jumpMoveCount = 0;
	_posX = 0, _posY = 0;
	_jumpPosX = 0, _jumpPosY = 0;
	_jumpVecX = 0, _jumpVecY = 0;
	_jumpMoveFlag = false;
	_jumpNowFlag = false;
	_liveFlag = false;
	_ropeModeFlag = false;
	_firstMoveFlag = false;
	_speedX = 0, _speedY = 0;
	_ropeMoveCount = 0;
	_angle = 0;
	_vertualPosX = 0, _vertualPosY = 0;
	_deletePosX = 0, _deletePosY = 0;
	_lastTouchIslandNumber = 0;
	_atackChargeCount = 0;
	_atackChargeflag = false;
	_atackModeFlag = false;
	_perceiveFlag = false;
	_resPosX = 0, _resPosY = 0;
	_dis_number = GetRand(3 - 1);
	_dethDelayCount = 0;
	_dethDelayFlag = false;
	_jumpFinishCount = 0;
	_jumpVPosX = 0, _jumpVPosY = 0;
	_onthThinkFlag = 0;

	_nextJumpPosX = 0;
	_nextJumpPosY = 0;
	_nextJumpIslandNumber = 0;

	_animPos_suraimu_idle = 0;
	_animPos_suraimu_jump = 0;
	_animPos_suraimu_deth = 0;
	_animPos_saru_idle = 0;
	_animPos_saru_walk = 0;
	_animPos_saru_jump = 0;
	_animPos_saru_deth = 0;
	_animPos_akuma_idle = 0;
	_animPos_akuma_move = 0;
	_animPos_akuma_attack = 0;
	_animPos_akuma_attackDelay = 15;
	_animPos_akuma_deth = 0;
	_animCount_suraimu_idle = 0;
	_animCount_suraimu_jump = 0;
	_animCount_suraimu_deth = 0;
	_animCount_saru_idle = 0;
	_animCount_saru_walk = 0;
	_animCount_saru_jump = 0;
	_animCount_saru_deth = 0;
	_animCount_akuma_idle = 0;
	_animCount_akuma_move = 0;
	_animCount_akuma_attack = 0;
	_animCount_akuma_attackDelay = 0;
	_animCount_akuma_deth = 0;
	_animFlag_akuma_attackDelay = 0;
}

void Enemy::Update()
{
	if (!_liveFlag)return;
	if (_dethDelayFlag) {
		_dethDelayCount--;

		switch (_dis_number) {
		case ENEMYTYPE_SLIME:
			_animCount_suraimu_deth++;
			if (_animCount_suraimu_deth % (60 / 9) == 0)_animPos_suraimu_deth++;
			if (_animPos_suraimu_deth >= 9)_animPos_suraimu_deth = 8;
			break;
		case ENEMYTYPE_MONKEY:
			_animCount_saru_deth++;
			if (_animCount_saru_deth % (60 / 9) == 0)_animPos_saru_deth++;
			if (_animPos_saru_deth >= 9)_animPos_saru_deth = 8;
			break;
		case ENEMYTYPE_DEMON:
			_animCount_akuma_deth++;
			if (_animCount_akuma_deth % (60 / 9) == 0)_animPos_akuma_deth++;
			if (_animPos_akuma_deth >= 9)_animPos_akuma_deth = 8;
			break;
		}

		if (_dethDelayCount <= 0)Init();
		return;
	}
	if (!_ropeModeFlag && !_firstMoveFlag && !_jumpMoveFlag)_jumpMoveCount++;
	if (_jumpMoveCount >= EnemyInfo::Enemy_Move_Count) {
		_jumpMoveFlag = true;
		_jumpMoveCount = 0;
	}
	if (_jumpNowFlag) {
		JumpMove();
	}
	if (_ropeModeFlag) RopeMove();
	if (_firstMoveFlag) {
		switch (_dis_number) {
		case ENEMYTYPE_MONKEY:
			_animCount_saru_walk++;
			if (_animCount_saru_walk % 4 == 0) {
				_animPos_saru_walk++;
			}
			if (_animPos_saru_walk >= 12) {
				_animPos_saru_walk = 0;
			}
		case ENEMYTYPE_DEMON:
			_animCount_akuma_move++;
			if (_animCount_akuma_move % 4 == 0) {
				_animPos_akuma_move++;
			}
			if (_animPos_akuma_move >= 6) {
				_animPos_akuma_move = 0;
			}
			break;
		}
		FirstMove();
	}
	if (_dis_number == ENEMYTYPE_DEMON) {
		if (RangeCheck()) {
			_atackModeFlag = true;
		}
	}
	if (_atackModeFlag) {
		_atackChargeCount++;
		if (_atackChargeCount > EnemyInfo::Attack_Charge_Count) {
			_atackChargeflag = true;
			_atackChargeCount = 0;
		}

		if (_animFlag_akuma_attackDelay == 1) {
			_animCount_akuma_attackDelay++;
			if (_animCount_akuma_attackDelay % 3 == 0) {
				_animPos_akuma_attackDelay++;
			}
			if (_animPos_akuma_attackDelay >= 20) {
				_animPos_akuma_attackDelay = 15;
				_animCount_akuma_attackDelay = 0;
				_animFlag_akuma_attackDelay = 0;
			}
		}
		
		_animCount_akuma_attack++;
		if (_animCount_akuma_attack % (EnemyInfo::Attack_Charge_Count / 15) == 0) {
			_animPos_akuma_attack++;
		}
		if (_animPos_akuma_attack >= 15) {
			_animPos_akuma_attack = 0;
			_animCount_akuma_attack = 0;
			_animFlag_akuma_attackDelay = 1;
		}
	}
	//if (_posX <= IslandInfo::Base_Island_PosX + 1 && _posX >= IslandInfo::Base_Island_PosX - 1
	//	&& _posY <= IslandInfo::Base_Island_PosY + 1 && _posY >= IslandInfo::Base_Island_PosY - 1) {
	//	Deth();
	//}
}

void Enemy::Draw()
{
	if (!_liveFlag)return;
	switch (_dis_number) {
	case ENEMYTYPE_SLIME:
		//DrawCircle((int)_posX, (int)_posY, EnemyInfo::Enemy_Rotation, GetColor(150, 150, 255), TRUE);
		//DrawGraph(_posX - _suraimu_width / 2, _posY - _suraimu_height / 2 - 10, _gh_suraimu, TRUE);
		if (_dethDelayFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _suraimu_width / 2, _posY - _suraimu_height / 2 - 10, _gh_suraimu_anim_deth[_animPos_suraimu_deth], 0.4f);
			break;
		}
		if (_jumpNowFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _suraimu_width / 2, _posY - _suraimu_height / 2 - 10, _gh_suraimu_anim_jump[_animPos_suraimu_jump], 0.4f);
			break;
		}
		_animCount_suraimu_idle++;
		if (_animCount_suraimu_idle % 6 == 0) {
			_animPos_suraimu_idle++;
		}
		if (_animPos_suraimu_idle >= 10) {
			_animPos_suraimu_idle = 0;
		}
		MyDrawTurn::Instance().SetDrawItem(_posX - _suraimu_width / 2, _posY - _suraimu_height / 2 - 10, _gh_suraimu_anim_idle[_animPos_suraimu_idle], 0.4f);
		break;
	case ENEMYTYPE_MONKEY:
		//DrawCircle((int)_posX, (int)_posY, EnemyInfo::Enemy_Rotation, GetColor(255, 255, 55), TRUE);
		//DrawGraph(_posX - _saru_width / 2, _posY - _saru_height / 2 - 10, _gh_saru, TRUE);
		if (_perceiveFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - 5, _posY - 80, _gh_perceive, 0.4f);
		}
		if (_dethDelayFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _saru_width / 2, _posY - _saru_height / 2 - 30, _gh_saru_anim_deth[_animPos_saru_deth], 0.4f);
			break;
		}
		if (_jumpNowFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _saru_width / 2, _posY - _saru_height / 2 - 60, _gh_saru_anim_jump[_animPos_saru_jump], 0.4f);
			break;
		}
		if (_firstMoveFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _saru_width / 2, _posY - _saru_height / 2 - 40, _gh_saru_anim_walk[_animPos_saru_walk], 0.4f);
			break;
		}
		_animCount_saru_idle++;
		if (_animCount_saru_idle % 6 == 0) {
			_animPos_saru_idle++;
		}
		if (_animPos_saru_idle >= 7) {
			_animPos_saru_idle = 0;
		}
		MyDrawTurn::Instance().SetDrawItem(_posX - _saru_width / 2, _posY - _saru_height / 2 - 20, _gh_saru_anim_idle[_animPos_saru_idle], 0.4f);
		break;
	case ENEMYTYPE_DEMON:
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
		//DrawCircle(_posX, _posY, ENEMY_RANGE, GetColor(255, 0, 0), TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//DrawCircle((int)_posX, (int)_posY, EnemyInfo::Enemy_Rotation, GetColor(150, 0, 200), TRUE);
		//DrawGraph(_posX - _akuma_width / 2, _posY - _akuma_height / 2 - 10, _gh_akuma, TRUE);
		if (_dethDelayFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _akuma_width / 2, _posY - _akuma_height / 2 - 30, _gh_akuma_anim_deth[_animPos_akuma_deth], 0.4f);
			break;
		}
		if (_jumpNowFlag || _firstMoveFlag) {
			MyDrawTurn::Instance().SetDrawItem(_posX - _akuma_width / 2, _posY - _akuma_height / 2 - 30, _gh_akuma_anim_move[_animPos_akuma_move], 0.4f);
			break;
		}
		if (_atackModeFlag || _animFlag_akuma_attackDelay == 1) {
			if (_animFlag_akuma_attackDelay == 0) {
				MyDrawTurn::Instance().SetDrawItem(_posX - _akuma_width / 2, _posY - _akuma_height / 2 - 30, _gh_akuma_anim_attack[_animPos_akuma_attack], 0.4f);
				break;
			}
			MyDrawTurn::Instance().SetDrawItem(_posX - _akuma_width / 2, _posY - _akuma_height / 2 - 30, _gh_akuma_anim_attack[_animPos_akuma_attackDelay], 0.4f);
			break;
		}
		_animCount_akuma_idle++;
		if (_animCount_akuma_idle % 6 == 0) {
			_animPos_akuma_idle++;
		}
		if (_animPos_akuma_idle >= 7) {
			_animPos_akuma_idle = 0;
		}
		MyDrawTurn::Instance().SetDrawItem(_posX - _akuma_width / 2, _posY - _akuma_height / 2 - 30, _gh_akuma_anim_idle[_animPos_akuma_idle], 0.4f);
		break;
	default:
		break;
	}
}

void Enemy::All()
{
	Update();
	Draw();
}

void Enemy::Deth()
{
	Init();
}

void Enemy::Deth_Fire()
{
	_dethDelayCount = 60;
	_dethDelayFlag = true;
}

void Enemy::Instantiate(int px, int py, int dis_number)
{
	_posX = _resPosX = px;
	_posY = _resPosY = py;
	_dis_number = dis_number;
	_liveFlag = true;
	_firstMoveFlag = true;
	_nextJumpPosX = _posX;
	_nextJumpPosY = _posY;
	_nextJumpIslandNumber = 0;
}

void Enemy::SetFirstPosition(int px, int py)
{
	_firstPosX = px;
	_firstPosY = py;
}

void Enemy::JumpStart(int posX, int posY)
{
	_jumpPosX = posX;
	_jumpPosY = posY;
	_jumpVecX = (_jumpPosX - _posX) / 56.0;
	_jumpVecY = (_jumpPosY - _posY) / 56.0;

	switch (_dis_number) {
	case ENEMYTYPE_SLIME:
		_jumpVecX = (_jumpPosX - _posX) / 36.0;
		_jumpVecY = (_jumpPosY - _posY) / 36.0;
		_animCount_suraimu_idle = 0;
		_animPos_suraimu_idle = 0;
		break;
	case ENEMYTYPE_MONKEY:
		_jumpVecX = (_jumpPosX - _posX) / 44.0;
		_jumpVecY = (_jumpPosY - _posY) / 44.0;
		_animCount_saru_idle = 0;
		_animPos_saru_idle = 0;
		break;
	case ENEMYTYPE_DEMON:
		_jumpVecX = (_jumpPosX - _posX) / 55.0;
		_jumpVecY = (_jumpPosY - _posY) / 55.0;
		_animCount_akuma_idle = 0;
		_animPos_akuma_idle = 0;
		break;
	}

	_jumpNowFlag = true;
}

void Enemy::JumpMove()
{
	_onthThinkFlag = false;
	switch (_dis_number) {
	case ENEMYTYPE_SLIME:
		_animCount_suraimu_jump++;
		if (_animPos_suraimu_jump < 10) {
			if (_animCount_suraimu_jump % 2 == 0) {
				_animPos_suraimu_jump++;
			}
		}
		else if (_animPos_suraimu_jump == 12) {
			if (_animCount_suraimu_jump % 8 == 0) {
				_animPos_suraimu_jump++;
			}
		}
		else {
			if (_animCount_suraimu_jump % 4 == 0) {
				_animPos_suraimu_jump++;
			}
		}
		if (_animPos_suraimu_jump >= 18) {
			_animPos_suraimu_jump = 17;
		}
		if (_animPos_suraimu_jump < 10)return;
		break;
	case ENEMYTYPE_MONKEY:
		SetPerceiveFlag(false);
		_animCount_saru_jump++;
		if (_animPos_saru_jump < 6) {
			if (_animCount_saru_jump % 2 == 0) {
				_animPos_saru_jump++;
			}
		}
		else if (_animPos_saru_jump >= 9 && _animPos_saru_jump <= 10) {
			if (_animCount_saru_jump % 7 == 0) {
				_animPos_saru_jump++;
			}
		}
		else {
			if (_animCount_saru_jump % 3 == 0) {
				_animPos_saru_jump++;
			}
		}
		if (_animPos_saru_jump >= 18) {
			_animPos_saru_jump = 17;
		}
		if (_animPos_saru_jump < 6)return;
		break;
	case ENEMYTYPE_DEMON:
		_animCount_akuma_move++;
		if (_animCount_akuma_move % 4 == 0) {
			_animPos_akuma_move++;
		}
		if (_animPos_akuma_move >= 6) {
			_animPos_akuma_move = 0;
		}
		break;
	default:
		break;
	}

	_jumpVPosX += _jumpVecX;
	_jumpVPosY += _jumpVecY;

	//_posX += _jumpVPosX;
	//_posY += _jumpVPosY;

	while (_jumpVPosX >= 1) {
		_jumpVPosX -= 1;
		_posX += 1;
	}
	while (_jumpVPosX <= -1) {
		_jumpVPosX += 1;
		_posX -= 1;
	}
	while (_jumpVPosY >= 1) {
		_jumpVPosY -= 1;
		_posY += 1;
	}
	while (_jumpVPosY <= -1) {
		_jumpVPosY += 1;
		_posY -= 1;
	}

	_jumpFinishCount++;
	switch (_dis_number) {
	case ENEMYTYPE_SLIME:
		if (_jumpFinishCount >= 36) {
			_posX = _jumpPosX;
			_posY = _jumpPosY;

			_jumpNowFlag = false;
			_jumpFinishCount = 0;
			_jumpVPosX = 0;
			_jumpVPosY = 0;
			_animCount_suraimu_jump = 0;
			_animPos_suraimu_jump = 0;
		}
		break;
	case ENEMYTYPE_MONKEY:
		if (_jumpFinishCount >= 44) {
			_posX = _jumpPosX;
			_posY = _jumpPosY;

			_jumpNowFlag = false;
			_jumpFinishCount = 0;
			_jumpVPosX = 0;
			_jumpVPosY = 0;
			_animCount_saru_jump = 0;
			_animPos_saru_jump = 0;
		}
		break;
	case ENEMYTYPE_DEMON:
		if (_jumpFinishCount >= 56) {
			_posX = _jumpPosX;
			_posY = _jumpPosY;

			_jumpNowFlag = false;
			_jumpFinishCount = 0;
			_jumpVPosX = 0;
			_jumpVPosY = 0;
			_animCount_akuma_move = 0;
			_animPos_akuma_move = 0;
		}
		break;
	default:
		if (_jumpFinishCount >= 56) {
			_posX = _jumpPosX;
			_posY = _jumpPosY;

			_jumpNowFlag = false;
			_jumpFinishCount = 0;
			_jumpVPosX = 0;
			_jumpVPosY = 0;
		}
		break;
	}
	//_posX = posX;
	//_posY = posY;
}

void Enemy::SetSpeed(double speedX, double speedY)
{
	_speedX = speedX;
	_speedY = speedY;
}

void Enemy::SetAngle(double angle)
{
	_angle = angle;
}

void Enemy::SetLastTouchIslandNumber(int lastTouchIslandNumber)
{
	if (lastTouchIslandNumber < 0 || lastTouchIslandNumber >= IslandInfo::Island_Num)return;
	_lastTouchIslandNumber = lastTouchIslandNumber;
}

void Enemy::OffJumpMoveFlag()
{
	_jumpMoveFlag = false;
}

void Enemy::OnRopeModeFlag()
{
	_ropeModeFlag = true;
}

void Enemy::OffRopeModeFlag()
{
	_ropeModeFlag = false;
}

void Enemy::Shot(Bullet * bullet, int targetPosX, int targetPosY)
{
	PlaySoundMem(_sh_attack_allow, DX_PLAYTYPE_BACK);
	_atackChargeflag = false;
	bullet->SetTarget(_posX, _posY, targetPosX, targetPosY);
}

void Enemy::Attack()
{
	if (_dis_number == 0)PlaySoundMem(_sh_attack_slime, DX_PLAYTYPE_BACK);
	if (_dis_number == 1)PlaySoundMem(_sh_attack_monkey, DX_PLAYTYPE_BACK);
}

void Enemy::SetPerceiveFlag(bool perceiveFlag)
{
	_perceiveFlag = perceiveFlag;
}

void Enemy::SetNextJumpInfo(int px, int py, int islandNum)
{
	_nextJumpPosX = px;
	_nextJumpPosY = py;
	_nextJumpIslandNumber = islandNum;
}

bool Enemy::RangeCheck()
{
	auto x = abs(IslandInfo::Base_Island_PosX - _posX);
	auto y = abs(IslandInfo::Base_Island_PosY - _posY);

	if (x * x + y * y <= (EnemyInfo::Enemy_Range + IslandInfo::Island_Rotation) * (EnemyInfo::Enemy_Range + IslandInfo::Island_Rotation)) {
		return true;
	}

	return false;
}

int Enemy::GetPosX()
{
	return _posX;
}

int Enemy::GetPosY()
{
	return _posY;
}

int Enemy::GetLastTouchIslandNumber()
{
	return _lastTouchIslandNumber;
}

double Enemy::GetAngle()
{
	return _angle;
}

bool Enemy::GetRopeModeFlag()
{
	return _ropeModeFlag;
}

bool Enemy::GetLiveFlag()
{
	return _liveFlag;
}

bool Enemy::GetDethDelayFlag()
{
	return _dethDelayFlag;
}

bool Enemy::GetJumpMoveFlag()
{
	return _jumpMoveFlag;
}

bool Enemy::GetJumpNowFlag()
{
	return _jumpNowFlag;
}

int Enemy::GetJumpPosX()
{
	return _jumpPosX;
}

int Enemy::GetJumpPosY()
{
	return _jumpPosY;
}

int Enemy::GetNextJumpPosX()
{
	return _nextJumpPosX;
}

int Enemy::GetNextJumpPosY()
{
	return _nextJumpPosY;
}

int Enemy::GetNextJumpIslandNumber()
{
	return _nextJumpIslandNumber;
}

int Enemy::GetFirstMoveFlag()
{
	return _firstMoveFlag;
}

void Enemy::RopeMove()
{
	_onthThinkFlag = 0;
	_ropeMoveCount++;
	if (_ropeMoveCount > 0) {
		_vertualPosX += _speedX + _deletePosX;
		_vertualPosY += _speedY + _deletePosY;

		_deletePosX = 0;
		_deletePosY = 0;

		if (_vertualPosX >= 1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosX - i < 1) {
					_deletePosX = _vertualPosX - i;
					_vertualPosX = 0;
					break;
				}
			}
			_posX += i;
		}
		else if (_vertualPosX <= -1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosX + i > -1) {
					_deletePosX = _vertualPosX + i;
					_vertualPosX = 0;
					break;
				}
			}
			_posX -= i;
		}
		if (_vertualPosY >= 1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosY - i < 1) {
					_deletePosY = _vertualPosY - i;
					_vertualPosY = 0;
					break;
				}
			}
			_posY += i;
		}
		else if (_vertualPosY <= -1) {
			int i;
			for (i = 1; i < 100; i++) {
				if (_vertualPosY + i > -1) {
					_deletePosY = _vertualPosY + i;
					_vertualPosY = 0;
					break;
				}
			}
			_posY -= i;
		}
	}
}

void Enemy::FirstMove()
{
	auto dx = _firstPosX - _resPosX;
	auto dy = _firstPosY - _resPosY;

	auto dxy = sqrt(dx * dx + dy * dy);

	_posX += dx / dxy;
	_posY += dy / dxy;

	if (abs(_posX - _resPosX) > abs(dx) || abs(_posY - _resPosY) > abs(dy)) {
		_firstMoveFlag = false;
		_posX = _firstPosX;
		_posY = _firstPosY;
	}
}
