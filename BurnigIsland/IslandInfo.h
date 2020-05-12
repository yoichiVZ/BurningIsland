#pragma once
#include "WindowInfo.h"

class IslandInfo {
public:
	// ���_X���W
	static const int Base_Island_PosX = WindowInfo::Screen_Width / 2;
	// ���_Y���W
	static const int Base_Island_PosY = WindowInfo::Screen_Height - 150;

	// ���̒��a
	static const int Island_Rotation = 25;

	// ���_�̒��a
	static const int Base_Island_Rotation = 60;

	// ���̐�
	static const int Island_Num = 50;
};