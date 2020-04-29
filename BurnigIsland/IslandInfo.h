#pragma once
#include "WindowInfo.h"

class IslandInfo {
public:
	// 拠点X座標
	static const int Base_Island_PosX = WindowInfo::Screen_Width / 2;
	// 拠点Y座標
	static const int Base_Island_PosY = WindowInfo::Screen_Height - 10;

	// 島の直径
	static const int Island_Rotation = 20;

	// 島の数
	static const int Island_Num = 41;
};