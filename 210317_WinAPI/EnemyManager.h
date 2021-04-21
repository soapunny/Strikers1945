#pragma once
#include "GameNode.h"

class Enemy;
class EnemyFactory;
class EnemyManager: public GameNode
{
public:
	enum ENEMY_FACTORY {SMALL_ENEMY, MEDIUM_ENEMY, BIG_ENEMY, END_ENEMY_FACTORY};
	enum ENEMY_INIT_POS{INIT_LEFT, INIT_CENTER, INIT_RIGHT, ENEMY_INIT_END};
private:
	vector<Enemy*> vEnemys;	
	//<Enemy>는 Enemy class크기만큼 가져오지만 
	//<Enemy*>는 포인터 크기인 4byte만 가져온다
	//< >는 템플릿
	FPOINT playerPos; 
	vector<EnemyFactory*> vEnemyFactories;

	int maxEnemyCnt;
	vector<FPOINT> vEnemyInitPos;

	float time;
	float createCycle;
	bool addEnemyToggle;

public:
	HRESULT Init();		// 오버라이딩 : 다형성
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(ENEMY_TYPE enemyType);
	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
};

