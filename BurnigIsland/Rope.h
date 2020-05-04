#pragma once
#include "Island.h"
#include "IslandInfo.h"

class Rope {
private:
	int _connectFlag[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _fireCount[IslandInfo::Island_Num][IslandInfo::Island_Num];
	bool _fireFlag[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _fireStartCount[IslandInfo::Island_Num][IslandInfo::Island_Num];
	bool _fireStartFlag[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _maxRopeLife;
	int _ropeLife;

public:
	double _posX[IslandInfo::Island_Num][IslandInfo::Island_Num];
	double _posY[IslandInfo::Island_Num][IslandInfo::Island_Num];
	int _moveCount[IslandInfo::Island_Num][IslandInfo::Island_Num];

	Rope();
	~Rope();
	// ������
	void Init();
	// �X�V
	void Update();
	void Draw();
	void All();
	// ���[�v���q����
	void Connect(int island1, int island2);
	// ���[�v���q���I������B
	void ConnectFinished(int island1, int island2);
	// ���[�v�S����
	void AllDelete();
	// ���[�v����
	void Minus();
	// ���[�v�S��
	void AllRecovery();
	// ���[�v��
	void Recovery();
	// ���[�v�ő�lUP
	void AddMaxLife();
	// ����
	void Ignition(int island1, int island2);
	// ���[�v��R�₷
	void Burn(int island1, int island2);

	// �ȉ� Get�֐�

	// �q�����Ă��邩
	int GetConnectFlag(int island1, int island2);
	// �R���Ă��邩
	bool GetFireFlag(int island1, int island2);
	// �R���n�߂Ă��邩
	bool GetFireStartFlag(int island1, int island2);
	// ���[�v���C�t�擾
	int GetRopeLife();
};