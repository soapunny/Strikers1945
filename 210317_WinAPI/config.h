// config.h

#pragma once
//#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>

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

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;