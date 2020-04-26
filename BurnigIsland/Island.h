#pragma once

#define CIRCLE_ROTATE 20
#define ISLAND_NUM 41

class Island {
private:
	enum IslandState {
		GRASS,
		FIRE,
		BURN,
	};
	IslandState _islandState;

	int _width, _height;
	int _rotation;
	bool _distanseFlag;
	bool _playerStayFlag;
	int _myNumber;
	int _fireCount, _burnCount;
	bool _fireStartFlag;
	int _fireStartCount;

public:
	int _posX, _posY;

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

	// �ȉ� Get�֐�
	int GetPosX();
	int GetPosY();
};