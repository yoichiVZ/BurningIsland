#pragma once

#define SETDRAWNUM_KILLCOUNT 0
#define SETDRAWNUM_WAVE 1

class DrawNumber {
private:
	int _gh_killCount[10];
	int _gh_wave[10];
	float _priority;

public:
	DrawNumber();
	void Draw(int posX, int posY, int vol, int drawNum);

private:
	void JudgSetNumber(int draw_gh[10], int drawNum);

};