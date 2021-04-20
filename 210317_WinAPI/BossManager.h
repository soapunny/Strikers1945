#pragma once
#include "GameNode.h"
#include "Subject.h"
class Boss;
class BossManager : public GameNode , public Subject
{
private:
	vector<Boss*> vBoss;	//3����
	SceneManager* sceneManagerObserver; //�ɼ��� ��Ͼ�� ��Ű����?
public:
	virtual void RegisterObserver(SceneManager* scenemanager) ;
	virtual void UnRegisterObserver() ;
	virtual void notifyObserve() ;
	HRESULT Init();		
	void Release();
	void Update();
	void Render(HDC hdc);
};

