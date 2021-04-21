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

	vector<Boss*> vBoss;	//3마리
	SceneManager* sceneManagerObserver; //옵서버 등록어떻게 시키더라?
	ItemManager* itemManagerObserver;
	RECT bossRect;			//boss 3마리 rect
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

