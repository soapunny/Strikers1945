#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// 프로젝트 자체에 포함 시킬 이미지
		FILE,			// 외부에서 로드할 이미지
		EMPTY,			// 자체 생산 이미지
		END
	};

	float k;
	float a;

	typedef struct tagImageInfo
	{
		DWORD resID;		// 리소스의 고유한 ID
		HDC hMemDC;			// 그리기를 주관하는 핸들
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int width;			// 이미지 가로 크기
		int height;			// 이미지 세로 크기
		BYTE loadType;		// 로드 타입

		HDC hBlendDC;			// 
		HBITMAP hBlendBitmap;	// 
		HBITMAP hOldhBlendBit;	// 

		HDC hTempDC;			// 
		HBITMAP hTempBitmap;	// 
		HBITMAP hOldhTempBit;	//
		HBRUSH hTempBrush;

		HDC hAngleTempDC[2];
		HBITMAP hAngleTempBitmap[2];
		HBITMAP hAngleOldTempBit[2];	
		HBRUSH hAngleTempBrush[2];

		HDC hAngleDC[2];
		HBITMAP hAngleBitmap[2];
		HBITMAP hAngleOldBit[2];

		// 애니메이션 관련 (프레임데이터)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;

			hBlendDC = NULL;
			hBlendBitmap = NULL;
			hOldhBlendBit = NULL;

			hTempDC = NULL;
			hTempBitmap = NULL;
			hOldhTempBit = NULL;
			hTempBrush = NULL;

			hAngleTempDC[0] = NULL;
			hAngleTempDC[1] = NULL;
			hAngleTempBitmap[0] = NULL;
			hAngleTempBitmap[1] = NULL;
			hAngleOldTempBit[0] = NULL;
			hAngleOldTempBit[1] = NULL;
			hAngleTempBrush[0] = NULL;
			hAngleTempBrush[1] = NULL;

			hAngleDC[0] = NULL;
			hAngleDC[1] = NULL;
			hAngleBitmap[0] = NULL;
			hAngleBitmap[1] = NULL;
			hAngleOldBit[0] = NULL;
			hAngleOldBit[1] = NULL;

			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;		// 이미지 정보 구조체 포인터
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;
	int reSize;

	BLENDFUNCTION blendFunc;

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 정적 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	//파일로부터 정적 각도 이미지를 로드하는 함수
	HRESULT AngleInit(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 동적 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0, bool isCenterRenderring = false);
	void Render(HDC hdc, int size, int destX, int destY, bool isCenterRenderring);
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring = false);
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring, int size);
	void AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring = false);
	void AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring, int currFrameX, int size);
	// 각도 렌더
	void AngleRender(HDC hdc, int destX, int destY, float angle, bool isCenterRenderring);

	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}

	BLENDFUNCTION* GetBlendFunc() { return &(this->blendFunc); }
};

