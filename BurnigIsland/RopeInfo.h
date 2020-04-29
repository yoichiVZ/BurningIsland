#pragma once

class RopeInfo {
public:
	// ロープの初期HP
	static const int Rope_Life = 10;

	// 着火してから燃えるまでの時間(フレーム)
	static const int Fire_Start_Count = 10;
	// 燃え始めてから燃え尽きるまでの時間(フレーム)
	static const int Fire_Count = 120;
};