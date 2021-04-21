#pragma once
#include "GameNode.h"
#include "Subject.h"
#include "ItemSubject.h"
class Boss;
class CollisionCheck;
class BossManager : public GameNode, public ItemSubject
{
private:
	CollisionCheck* collisionCheck;

	vector<Boss*> vBoss;	//3����
	SceneManager* sceneManagerObserver; //�ɼ��� ��Ͼ�� ��Ű����?
	ItemManager* itemManagerObserver;
	RECT bossRect;			//boss 3���� rect
	FPOINT bossPos;
	
	

public:

	HRESULT Init();
	HRESULT Init(CollisionCheck* collisionCheck, FPOINT* playerPos);

	virtual void RegisterObserver(SceneManager* scenemanager) ;
	virtual void RegisterObserver(ItemManager* itemManager);
	virtual void UnRegisterObserver() ;
	virtual void ItemUnRegisterObserver();
	virtual void notifyObserve() ;
	virtual void ItemnotifyObserve();
	virtual DROPENEMY GetDropEnemy() { return BOSSDROP; }

	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetBossPos(FPOINT bossPos) { this->bossPos = bossPos; }
	inline RECT GetBossRect() { return bossRect; }
	inline FPOINT GetBossPos() { return bossPos; }
};

