#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
	timer = new Timer;
	timer->init();

	return S_OK;
}

void TimerManager::Release()
{
	SAFE_DELETE(timer);
}

void TimerManager::Update()
{
	if (timer)
	{
		timer->Tick();
	}
}

void TimerManager::Render(HDC hdc)
{
	if (timer)
	{
		wsprintf(szText, "FPS: %d", timer->getFPS());
		TextOut(hdc, WINSIZE_X-150, 20, szText, strlen(szText));

		wsprintf(szText, "경과 시간: %d",timer->getGameSecond());
		TextOut(hdc, 200, 20, szText, strlen(szText));
	}
}

float TimerManager::getElapsedTime()
{
	return timer->getElapsedTime();
}
