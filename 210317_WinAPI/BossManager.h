#pragma once
#include "GameNode.h"
#include "Subject.h"

class Boss;
class CollisionCheck;


class BossManager : public GameNode
{
private:
	CollisionCheck* collisionCheck;

	vector<Boss*> vBoss;	//3마리
	SceneManager* sceneManagerObserver; //옵서버 등록어떻게 시키더라?

	RECT bossRect;			//boss 3마리 rect
	FPOINT bossPos;
	FPOINT bossPosItem[3];
	bool isBossAlive;
	bool isBoss1Alive;
	bool isBoss2Alive;
	bool isBoss3Alive;
	bool AisBoss1Alive;
	bool AisBoss2Alive;
	bool AisBoss3Alive;
	DROPENEMY dropEnemy;
public:

	HRESULT Init();
	HRESULT Init(CollisionCheck* collisionCheck, FPOINT* playerPos);

	virtual void RegisterObserver(SceneManager* scenemanager) ;

	virtual void UnRegisterObserver() ;

	virtual void notifyObserve() ;

	//virtual DROPENEMY GetDropEnemy() { return BOSSDROP; }

	void Release();
	void Update();
	void Render(HDC hdc);

	inline bool GetIsAlive(){return isBossAlive;}
	inline void SetBossPos(FPOINT bossPos) { this->bossPos = bossPos; }
	inline RECT GetBossRect() { return bossRect; }
	inline FPOINT GetBossPos() { return bossPos; }
	inline bool  GetisBoss1Alive() { return isBoss1Alive; }
	inline bool  GetisBoss2Alive() { return isBoss2Alive; }
	inline bool  GetisBoss3Alive() { return isBoss3Alive; }
	inline bool  GetAisBoss1Alive() { return AisBoss1Alive; }
	inline bool  GetAisBoss2Alive() { return AisBoss2Alive; }
	inline bool  GetAisBoss3Alive() { return AisBoss3Alive; }
	inline FPOINT GetBoss1Pos() {return bossPosItem[0];}
	inline FPOINT GetBoss2Pos() { return bossPosItem[1]; }
	inline FPOINT GetBoss3Pos() { return bossPosItem[2]; }

	
};

