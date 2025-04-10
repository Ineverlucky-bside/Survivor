#include <graphics.h>
#include <string>

int idxCurrentAnim = 0; //����֡����

const int PLAYER_ANIM_NUM = 4; //����֡��������

IMAGE imgPlayerDown[PLAYER_ANIM_NUM];
IMAGE imgPlayerUp[PLAYER_ANIM_NUM];

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

	bool running = true;
	ExMessage msg;

	BeginBatchDraw();

	setbkcolor(RGB(144, 238, 144));//��䱳����ɫ


	while (running)
	{
		DWORD startTime = GetTickCount();

		while (peekmessage(&msg))
		{

		}

		static int counter = 0; //��¼��ǰ��Ϸ֡һ�������˶��ٶ���֡

		if (++counter % 5 == 0) //ÿ5����Ϸ֡����һ������֡
			idxCurrentAnim++;

		idxCurrentAnim = idxCurrentAnim % PLAYER_ANIM_NUM; //֡��������֡����֮�����

		cleardevice();
		FlushBatchDraw();

		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 144)
		{
			Sleep(1000 / 144 - deltaTime);
		}
	}

	EndBatchDraw();
}