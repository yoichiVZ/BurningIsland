#include <DxLib.h>
#include "MyDrawTurn.h"

#include <algorithm>

MyDrawTurn & MyDrawTurn::Instance()
{
	static std::unique_ptr<MyDrawTurn> instance(new MyDrawTurn);

	return *instance;

}

void MyDrawTurn::Init()
{
	while (!draw_items.empty()) {
		draw_items.pop_back();
	}
}

void MyDrawTurn::SetDrawItem(int x1, int y1, int graphicHandle, float priority, int DrawType, float angle, int BlendMode, int BlendParam, int x2, int y2)
{
	DrawInfo assginment;
	assginment.SetInfo(x1, y1, graphicHandle, priority, DrawType, angle, BlendMode, BlendParam, x2, y2);
	draw_items.push_back(assginment);
}

void MyDrawTurn::SortDrawItem()
{
	std::sort(draw_items.begin(), draw_items.end(), [](const DrawInfo& x, const DrawInfo& y) { return x._priority < y._priority; });
}

void MyDrawTurn::DrawAll()
{
	for (std::vector<DrawInfo>::const_iterator itr = draw_items.begin(); itr != draw_items.end(); itr++) {
		SetDrawBlendMode(itr->_BlendMode, itr->_BlendParam);

		switch (itr->_DrawType) {
		case DRAWTYPE_DRAWGRAPH:
			DrawGraph(itr->_x1, itr->_y1, itr->_graphicHandle, TRUE);
			break;
		case DRAWTYPE_DRAWLINE:
			DrawLine(itr->_x1, itr->_y1, itr->_x2, itr->_y2, GetColor(255, 0, 0), 3);
			break;
		case DRAWTYPE_DRAWROTAGRAPH:
			DrawRotaGraph(itr->_x1, itr->_y1, 1.0, itr->_angle, itr->_graphicHandle, TRUE);
			break;
		default:
			break;
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
