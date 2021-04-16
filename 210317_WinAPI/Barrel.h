#pragma once
#include "GameNode.h"

class MissileManager;
class Barrel
{
private:
	// ����(������ ������, ����)	���� �ʿ�
	FPOINT barrelStart;
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// �̻���
	MissileManager* myMissile; //���� �ʿ�
	int fireCount;
public:
	HRESULT Init(FPOINT pos);
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
};

