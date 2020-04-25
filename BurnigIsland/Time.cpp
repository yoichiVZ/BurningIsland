#include "Time.h"

Time::Time()
{
	Init();
}

void Time::Init()
{
	_gameTime = 0;
}

void Time::TimeCourse()
{
	_gameTime++;
}

int Time::GetGameTime()
{
	return _gameTime;
}
