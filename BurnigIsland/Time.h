#pragma once

class Time {
private:
	int _gameTime;

public:
	Time();
	void Init();
	void TimeCourse();
	int GetGameTime();
};