#pragma once
#include "Island.h"

#define ROPELIFE_NUM 800

class Rope {
private:
	bool _connectFlag[ISLAND_NUM][ISLAND_NUM];
	int _fireCount[ISLAND_NUM][ISLAND_NUM];
	bool _fireFlag[ISLAND_NUM][ISLAND_NUM];
	int _ropeLife;

public:
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
	// ���[�v�S����
	void AllDelete();
	// ���[�v����
	void Minus(int minus);
	// ���[�v�S��
	void AllRecovery();
	// ���[�v��R�₷
	void Burn(int island1, int island2);

	// �ȉ� Get�֐�

	// �q�����Ă��邩
	bool GetConnectFlag(int island1, int island2);
	// �R���Ă��邩
	bool GetFireFlag(int island1, int island2);
	// ���[�v���C�t�擾
	int GetRopeLife();
};