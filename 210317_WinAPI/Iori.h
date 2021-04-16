#pragma once
#include "GameNode.h"

class Image;
class Iori : public GameNode
{
private:
	Image* img;
	FPOINT pos;
	int elapsedTime;	// 100�� �� ������ �ִϸ��̼� �������� 1�� ����
	int frame;			// �ִϸ��̼� ������ 0 ~ 8

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

};

