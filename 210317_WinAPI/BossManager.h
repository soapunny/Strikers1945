#pragma once
#include "GameNode.h"
#include "Subject.h"

class Boss;
class CollisionCheck;
class BossManager : public GameNode , public Subject
{
private:
	CollisionCheck* collisionCheck;

	vector<Boss*> vBoss;	//3마리
	SceneManager* sceneManagerObserver; //옵서버 등록어떻게 시키더라?
	RECT bossRect;			//boss 3마리 rect
	Image* img;
	int currFrame;
	int maxFrame;
	int frameTime;
	int currBossNumber;
	int printNumber;
public:

	HRESULT Init();
	HRESULT Init(CollisionCheck* collisionCheck, FPOINT* playerPos);

	virtual void RegisterObserver(SceneManager* scenemanager) ;
	virtual void UnRegisterObserver() ;
	virtual void notifyObserve() ;

	void Release();
	void Update();
	void Render(HDC hdc);
	
	bool GetEnding();
	inline RECT GetBossRect() { return bossRect; }
};

