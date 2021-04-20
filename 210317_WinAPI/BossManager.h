#pragma once
#include "GameNode.h"

class Boss;
class BossManager : public GameNode
{
private:
	vector<Boss*> vBoss;	//3¸¶¸®

public:
	HRESULT Init();
	HRESULT Init(FPOINT* playerPos);
	void Release();
	void Update();
	void Render(HDC hdc);
};

