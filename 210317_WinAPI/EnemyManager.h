#pragma once
#include "GameNode.h"

class Enemy;
class EnemyFactory;
class CollisionCheck;
class EnemyManager: public GameNode
{
public:
	enum ENEMY_FACTORY {SMALL_ENEMY, MEDIUM_ENEMY, BIG_ENEMY, END_ENEMY_FACTORY};
	enum ENEMY_INIT_POS{INIT_LEFT, INIT_CENTER, INIT_RIGHT, ENEMY_INIT_END};
private:
	vector<Enemy*> vEnemys;	
	//<Enemy>�� Enemy classũ�⸸ŭ ���������� 
	//<Enemy*>�� ������ ũ���� 4byte�� �����´�
	//< >�� ���ø�
	FPOINT playerPos; 
	vector<EnemyFactory*> vEnemyFactories;

	int maxEnemyCnt;
	vector<FPOINT> vEnemyInitPos;

	float time;
	float createCycle;
	bool addEnemyToggle;

	CollisionCheck* collisionCheck;

public:
	HRESULT Init() { return S_OK; }		// �������̵� : ������
	HRESULT Init(CollisionCheck* collisionCheck);		// �������̵� : ������
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(ENEMY_TYPE enemyType, ENEMY_INIT_POS enemyInitPos);
	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
};

