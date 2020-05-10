#pragma once

class Island {
private:
	enum IslandState {
		GRASS,
		FIRE,
		BURN,
	};
	IslandState _islandState;

	int _posX, _posY;
	int _width, _height;
	int _rotation;
	bool _distanseFlag;
	bool _playerStayFlag;
	int _myNumber;
	int _fireCount, _burnCount;
	bool _fireStartFlag;
	int _fireStartCount;
	bool _extinguishedFlag;

	int _gh_island;
	int _gh_burnIsland;
	int _gh_base;
	int _base_width, _base_height;

	int _gh_burningIsland[10];
	int _animPos_burningIsland;
	int _animCount_burningIslnad;

	int _gh_revivalingIsland[8];
	int _animPos_revivalingIsland;
	int _animCount_revivalingIsland;

	int _sh_fire;

public:

	Island();
	~Island();
	void Init();
	void Update();
	void Draw();
	void All();
	// ���[�v���q����͈͓���
	bool DistanseCheck(int px, int py);
	// �v���C���[�����ɂ��邩
	bool PlayerStayCheck(int px, int py);
	// �ړ��ł���͈͓���
	bool EnemyDistanseCheck(int ex, int ey);
	// �G�l�~�[�����ɂ��邩
	bool EnemyStayCheck(int ex, int ey);
	void CrossCheck(Island* island);
	void GetMyNumber(int num);
	// ����
	void Burning();
	// ����
	void Ignition();
	// ���W�Z�b�g
	void SetPosition(int posX, int posY);
	// ������
	void Revival();

	// ���̏�Ԃ�GRASS��
	bool StateCheck_GRASS();
	// ���̏�Ԃ�FIRE��
	bool StateCheck_FIRE();
	// ���̏�Ԃ�BURN��
	bool StateCheck_BURN();
	// ���΂�����
	bool ExtinguishedCheck();

	// �ȉ� Get�֐�
	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();

	void MoveX(int num);
	void MoveY(int num);
};