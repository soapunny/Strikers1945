#pragma once
#include "GameNode.h"

class MissileManager;
class Barrel
{
private:
	// 포신(포신의 시작점, 끝점)	동적 필요
	FPOINT barrelStart;
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;

	// 미사일
	MissileManager* myMissile; //동적 필요
	int fireCount;
public:
	HRESULT Init(FPOINT pos);
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
};

