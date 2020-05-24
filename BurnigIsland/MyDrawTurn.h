#pragma once
#include <memory>
#include <vector>

#define BLENDMODE_NOBLEND 0
#define BLENDMODE_ALPHA 1
#define BLENDMODE_ADD 2
#define DRAWTYPE_DRAWGRAPH 0
#define DRAWTYPE_DRAWLINE 1
#define DRAWTYPE_DRAWROTAGRAPH 2
#define DRAWTYPE_DRAWEXTENDGRAPH 3

class MyDrawTurn final {
private:
	MyDrawTurn() {}

	MyDrawTurn(const MyDrawTurn&) {}

	MyDrawTurn& operator = (const MyDrawTurn&) {}

public:
	// インスタンス取得メソッド
	static MyDrawTurn& Instance();

	// 初期化
	void Init();

	// vectorに追加
	void SetDrawItem(int x1, int y1, int graphicHandle, float priority, int DrawType = 0,double ExRate = 1, double angle = 0, int BlendMode = 0, int BlendParam = 0, int x2 = 0, int y2 = 0);

	void SetDrawBrightItem(int x1, int y1, int graphicHandle, float priority, int redBright, int greenBright, int blueBright, int BlendMode = 0, int BlendParam = 0, int DrawType = 0, double angle = 0, int x2 = 0, int y2 = 0);

	// vectorをソート
	void SortDrawItem();

	// 描画
	void DrawAll();

private:
	struct DrawInfo {
		int _x1, _y1, _x2, _y2;
		int _graphicHandle;
		float _priority;
		double _ExRate;
		double _angle;
		// 0 = DrawGraph
		// 1 = DrawLine
		// 2 = DrawRotaGraph
		int _DrawType;
		// 0 = NOBLEND
		// 1 = ALPHA
		// 2 = ADD
		int _BlendMode;
		int _BlendParam;
		int _RedBright;
		int _GreenBright;
		int _BlueBright;
		bool _BrightFlag;

		DrawInfo() {
			_x1 = 0, _y1 = 0, _x2 = 0, _y2 = 0;
			_graphicHandle = 0;
			_priority = 0.0f;
			_ExRate = 1;
			_angle = 0;
			_DrawType = 0;
			_BlendMode = 0;
			_BlendParam = 0;
			_RedBright = 0;
			_GreenBright = 0;
			_BlueBright = 0;
			_BrightFlag = false;
		}

		void SetInfo(int x1,int y1, int graphicHandle, float priority, int DrawType, double ExRate,double angle, int BlendMode, int BlendParam, int x2, int y2) {
			_x1 = x1;
			_y1 = y1;
			_x2 = x2;
			_y2 = y2;
			_graphicHandle = graphicHandle;
			_priority = priority;
			_ExRate = ExRate;
			_angle = angle;
			_DrawType = DrawType;
			_BlendMode = BlendMode;
			_BlendParam = BlendParam;
			_BrightFlag = false;
		}

		void SetBrightInfo(int x1, int y1, int graphicHandle, float priority, int redBright, int greenBright, int blueBright, int BlendMode , int BlendParam, int DrawType, double angle, int x2, int y2) {
			_x1 = x1;
			_y1 = y1;
			_x2 = x2;
			_y2 = y2;
			_graphicHandle = graphicHandle;
			_priority = priority;
			_angle = angle;
			_DrawType = DrawType;
			_BlendMode = BlendMode;
			_BlendParam = BlendParam;
			_RedBright = redBright;
			_GreenBright = greenBright;
			_BlueBright = blueBright;
			_BrightFlag = true;
		}
	};
	std::vector<DrawInfo> draw_items;
};