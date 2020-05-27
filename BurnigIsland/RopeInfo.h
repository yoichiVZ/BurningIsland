#pragma once

class RopeInfo {
public:
	// ロープの初期HP
	static const int Rope_Life = 8;
	// ロープの増加限界
	static const int Rope_MaxLife = 17;

	// 着火してから燃えるまでの時間(フレーム)
	static const int Fire_Start_Count = 10;
	// 燃え始めてから燃え尽きるまでの時間(フレーム)
	static const int Fire_Count = 60;
};