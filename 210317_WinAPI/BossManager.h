#pragma once
#include "GameNode.h"

class Boss;
class BossManager : public GameNode
{
private:
	vector<Boss*> vBoss;	//3����
	RECT bossRect;			//boss 3���� rect

public:
	HRESULT Init();		
	void Release();
	void Update();
	void Render(HDC hdc);

	inline RECT GetBossRect() { return bossRect; }
};

