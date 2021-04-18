#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;

class EnemyManager: public GameNode
{
private:
	vector<Enemy*> vEnemys;	
	//<Enemy>는 Enemy class크기만큼 가져오지만 
	//<Enemy*>는 포인터 크기인 4byte만 가져온다
	//< >는 템플릿
	FPOINT playerPos;

public:
	HRESULT Init();		// 오버라이딩 : 다형성
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);
	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
};

