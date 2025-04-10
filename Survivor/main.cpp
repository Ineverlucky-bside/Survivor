#include <graphics.h>
#include <string>

int idxCurrentAnim = 0; //动画帧索引

const int PLAYER_ANIM_NUM = 4; //动画帧总数常量

IMAGE imgPlayerDown[PLAYER_ANIM_NUM];
IMAGE imgPlayerUp[PLAYER_ANIM_NUM];

#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });	
}

void LoadAnimation()
{
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"Sprites/Hero/idle_down (" + std::to_wstring(i) + L").png";
		loadimage(&imgPlayerDown[i], path.c_str());
	}

	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"Sprites/Hero/idle_up (" + std::to_wstring(i) + L").png";
		loadimage(&imgPlayerUp[i], path.c_str());
	}
}

int main()
{
	initgraph(1280, 720);
	setbkcolor(RGB(144, 238, 144));//填充背景颜色
	LoadAnimation();

	bool running = true;
	ExMessage msg;

	BeginBatchDraw();

	while (running)
	{
		DWORD startTime = GetTickCount();

		while (peekmessage(&msg))
		{

		}

		static int counter = 0; //记录当前游戏帧一共播放了多少动画帧
		if (++counter %5 == 0) //每5个游戏帧播放一个动画帧
			idxCurrentAnim++;

		idxCurrentAnim = idxCurrentAnim % PLAYER_ANIM_NUM; //帧索引超过帧总数之后归零

		cleardevice();

		putimage_alpha(500, 500, &imgPlayerDown[idxCurrentAnim]);

		FlushBatchDraw();

		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 60)
		{
			Sleep(1000 / 60 - deltaTime);
		}
	}

	EndBatchDraw();
}