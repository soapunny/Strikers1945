#pragma once
#include "GameNode.h"

class Tank;
class BossManager;
class EnemyManager;
class Image;
class PlayerShip;
class CollisionCheck;

class MainGame : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* backBuffer;
	Image* backGround;
	FPOINT backGroundPos;
	Image* backCloud;

	Tank* tank;

	//int enemyCount;
	//Enemy* enemy;
	EnemyManager* enemyManager;

	PlayerShip* playerShip;

	BossManager* bossManager;

	CollisionCheck* collisionCheck;

public:
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	void Render();
	virtual void Render(HDC hdc) {};

	void CheckCollision();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

