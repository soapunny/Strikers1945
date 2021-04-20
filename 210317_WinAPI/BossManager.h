#pragma once
#include "GameNode.h"

class Boss;
class BossManager : public GameNode
{
private:
	vector<Boss*> vBoss;	//3마리
	RECT bossRect;			//boss 3마리 rect

public:
	HRESULT Init();		
	void Release();
	void Update();
	void Render(HDC hdc);

	inline RECT GetBossRect() { return bossRect; }
};

