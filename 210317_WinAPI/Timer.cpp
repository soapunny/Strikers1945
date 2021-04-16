#include "Timer.h"

HRESULT Timer::init()
{
	isHardware = false;			
	timeScale = 0.0f;			
	timeElapsed = 0.0f;
	currTime = 0.0;			
	lastTime = 0.0;			
	periodFrequency = 0.0;

	fpsTimeElapsed = 0.0f;
	fpsFrameCount = 0;
	gameSecond = 0;
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))	// cpu �ʴ� �������� �޾� �� �� �ִ� ���
	{
		isHardware = true; 
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);				// ��� ������
		timeScale = 1.0f / periodFrequency;								// (1�� / cpu �ʴ� ������) (1/10 ����..)
	}
	else
	{
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}

	return S_OK;
}

void Timer::Tick()
{
	// ���� ������ or ���� �ð��� ���ؼ� ��� �ð��� ���
	if(isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}

	timeElapsed = (currTime - lastTime) * timeScale;	//��� �ð��� ��� ((6-3)*(1/10) ����..)

	//������ ���
	fpsTimeElapsed += timeElapsed;
	fpsFrameCount++;

	if (fpsTimeElapsed >= 1.0f)
	{
		gameSecond += 1;
		FPS = fpsFrameCount;
		fpsFrameCount = 0.0f;
		fpsTimeElapsed -= 1.0f;
	}

	lastTime = currTime;								//timeElapsed�� ��� ���ϴ� ���� ����
}
