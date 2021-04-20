#pragma once
#include "GameNode.h"
#include "Subject.h"
class Boss;
class BossManager : public GameNode , public Subject
{
private:
	vector<Boss*> vBoss;	//3마리
	SceneManager* sceneManagerObserver; //옵서버 등록어떻게 시키더라?
public:

	HRESULT Init();
	HRESULT Init(FPOINT* playerPos);

	virtual void RegisterObserver(SceneManager* scenemanager) ;
	virtual void UnRegisterObserver() ;
	virtual void notifyObserve() ;

	void Release();
	void Update();
	void Render(HDC hdc);
};

