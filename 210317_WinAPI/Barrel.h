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
	inline void SetbarrelEnd( FPOINT barrelEnd) { this->barrelEnd = barrelEnd; }

	inline FPOINT GetstartPos() {return barrelStart;}//포신을 보스에서 돌려줄려고 가져옴
	inline float GetAngle() { return barrelAngle; }
	inline int GetSize() { return barrelSize; }
	//inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
};

