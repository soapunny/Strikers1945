#pragma once
#include "GameNode.h"
#include "Subject.h"

class Tank;
class BossManager;
class EnemyManager;
class ItemManager;
class Image;
class PlayerShip;
class CollisionCheck;
class SceneManager;

class MainGame : public GameNode, public Subject  //두개를 상속받을수 있다.
{
private:
	
	bool isInited;
	int status;
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* backBuffer;
	Image* backGround;
	
	Image* openingImage;
	Image* endingImage;

	FPOINT backGroundPos;
	Image* backCloud;

	Tank* tank;

	//int enemyCount;
	//Enemy* enemy;
	EnemyManager* enemyManager;

	SceneManager* sceneManagerObserver;//옵저버 씬매니저

	ItemManager* itemManagerObserver;

	PlayerShip* playerShip;

	BossManager* bossManager;

	CollisionCheck* collisionCheck;

	
public:
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	void Render();
	
	virtual void Render(HDC hdc) {};

	virtual void RegisterObserver(SceneManager* scenemanager);
	virtual void RegisterObserver(ItemManager* scenemanager);
	virtual void UnRegisterObserver() ;
	virtual void notifyObserve();

	void CheckCollision();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

