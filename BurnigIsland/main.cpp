#include <DxLib.h>
#include "WindowInfo.h"
#include "GameController.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(WindowInfo::Screen_Width, WindowInfo::Screen_Height, 32);
	if (DxLib_Init() == -1)return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	GameController* gameController = new GameController();

	while (ProcessMessage() != -1)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
		int startTime = GetNowCount();
		ClearDrawScreen();

		gameController->All();
		//if (CheckHitKey(KEY_INPUT_Q) == 1)
		//	SaveDrawScreenToPNG(0, 0, WindowInfo::Screen_Width, WindowInfo::Screen_Height, "game3.png");

		ScreenFlip();
		int endTime = GetNowCount();
		WaitTimer((1000 / 60) - (endTime - startTime));
	}

	delete gameController;

	DxLib_End();
	return 0;
}