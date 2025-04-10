#include <graphics.h>
#include <string>

int idxCurrentAnim = 0; //����֡����

const int PLAYER_ANIM_NUM = 4; //����֡��������

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
	setbkcolor(RGB(144, 238, 144));//��䱳����ɫ
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

		static int counter = 0; //��¼��ǰ��Ϸ֡һ�������˶��ٶ���֡
		if (++counter %5 == 0) //ÿ5����Ϸ֡����һ������֡
			idxCurrentAnim++;

		idxCurrentAnim = idxCurrentAnim % PLAYER_ANIM_NUM; //֡��������֡����֮�����

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