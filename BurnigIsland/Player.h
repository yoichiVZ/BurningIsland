#pragma once

//#define PLAYER_ROTATE 10
//#define ROPE_DISTANSE 100

class Player {
private:
	int _posX, _posY;
	int _hp;

	int _sh_damage;

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
	void All();
	// �_���[�W
	void Damage();
	// �ړ�
	void Move(int posX, int posY);

	// �ȉ� Get�֐�

	// X���W�擾
	int GetPosX();
	// Y���W�擾
	int GetPosY();
	// HP�擾
	int GetHP();
	// ������Ԏ擾
	bool GetLive();
};