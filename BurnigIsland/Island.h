#pragma once

#define CIRCLE_ROTATE 20
#define ISLAND_NUM 33

class Island {
public:
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
	int _mouseCount_Right;
	int _myNumber;
	int _fireCount, _burnCount;
	bool _fireStartFlag;
	int _fireStartCount;

	Island();
	~Island();
	void Init();
	void Update();
	void Draw();
	void All();
	bool DistanseCheck(int px, int py);
	bool PlayerStayCheck(int px, int py);
	bool EnemyDistanseCheck(int ex, int ey);
	bool EnemyStayCheck(int ex, int ey);
	void CrossCheck(Island* island);
	void GetOnMouseRight(int mouseCount);
	void GetMyNumber(int num);
	void Burning();
};