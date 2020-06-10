#pragma once

#define SETDRAWNUM_KILLCOUNT 0
#define SETDRAWNUM_WAVE 1
#define SETDRAWNUM_RESULTWAVE 2
#define SETDRAWNUM_WAVEUP 3

class DrawNumber {
private:
	int _gh_killCount[10];
	int _gh_wave[10];
	int _gh_resultWave[10];
	int _gh_waveUp[10];
	float _priority;

public:
	DrawNumber();
	void Draw(int posX, int posY, int vol, int drawNum);
	void DrawBright(int posX, int posY, int vol, int drawNum, int redBright, int greenBright, int blueBright, int BlendMode, int BlendParam);

private:
	void JudgSetNumber(int draw_gh[10], int drawNum);

};