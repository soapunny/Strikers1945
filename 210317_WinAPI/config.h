// config.h

#pragma once
//#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>
#include <vector>
#include<list>

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"

using namespace std;

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define PI 3.141592f
#define DegToRad(x) ((x) * PI / 180.0f)	//Degree To Radian
#define SAFE_DELETE(p) { if(p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { p->Release(); delete p; p = nullptr; } }

enum MOVETYPE {
	NORMAL_MOVE, CENTER_MOVE, COME_AND_GO_MOVE, LEFT_DOWN_MOVE
	, LEFT_MOVE, LEFT_SIN_MOVE, PHASE_CHANGE_MOVE, LEFT_UP_MOVE, POINT_MOVE
	, RIGHT_DOWN_MOVE, RIGHT_MOVE, RIGHT_SIDE_MOVE, RIGHT_SIN_MOVE, RIGHT_UP_MOVE
	, SPEAR_MOVE, ZIGZAG_MOVE, BILLIARDS_MOVE, END_MOVE
};

enum FIRETYPE { NormalFIRE, FallingKnivesFIRE, FIREWORKFIRE, GuidedFIRE, 
	PlayerFIRE, ZigzagFIRE, MeteorFIRE, WormFIRE, TwoFIRE, NotFIRE,TornadoFIRE, END_FIRETYPE };

enum ENEMY_TYPE { SMALL_ENEMY, MEDIUM_ENEMY, BIG_ENEMY, ENEMY_TYPE_END };

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;