#pragma once
#include "config.h"
// 1�ʿ� �̵��ϴ� �Ÿ��� ������ �θ�
// ��ǻ�� ���� 1�ʿ� ó���ϴ� ������ ���� �޶�
// 1�� ���� ����� �����ϰ� ��Ÿ����
// �̸� ����Ϸ���, ���� ����ϰ� �ִ� ��ǻ����
// ��Ȯ�� �ð��� ���ϴ� ���� �ʿ��ϴ�

// 1�ʿ� 10�� ������ �Ѵ� 
// �ð��� �����ϴ� �������� �������� 3�̰�, �������� �������� 6�� ��
// �� 3�� ���� �Ͽ���
// �ð��� ���ϱ� ���� ���� �����
// 1��:10�� = x��:3��

class Timer
{
private:
	bool isHardware;			// ���� Ÿ�̸�(cpu clock)�� �� �� �ִ��� ����
	float timeScale;			// ��� ������(���� - ����)�� �ʴ� �������� ������ �������� �ð����� ȯ��
	float timeElapsed;			// ������ �ð��� ���� �ð��� �����
	__int64 currTime;			// ���� �ð�(���� Ÿ�̸� ������)
	__int64 lastTime;			// ���� �ð�(���� Ÿ�̸� ������)
	__int64 periodFrequency;	// ���� Ÿ�̸� ���ļ�(�ʴ� ������)

	float fpsTimeElapsed;			// timeElapsed ���� -> ������ ��� �ð�(1�ʰ� �������� Ȯ�� �ϱ� ���� �뵵)
	unsigned long fpsFrameCount;	// �ʴ� ������ �� Ȯ�ο�
	unsigned long FPS;				// �ʴ� ������ ��

	int gameSecond;

public:
	HRESULT init();
	void Tick();

	inline unsigned long getFPS() { return this->FPS; }
	inline float getElapsedTime() { return this->timeElapsed; }
	inline int getGameSecond() { return this->gameSecond; }
};

