#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			// �ܺο��� �ε��� �̹���
		EMPTY,			// ��ü ���� �̹���
		END
	};

	float k;
	float a;

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ������ ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

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

		// �ִϸ��̼� ���� (�����ӵ�����)
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
	IMAGE_INFO* imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;
	int reSize;

	BLENDFUNCTION blendFunc;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� ���� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	//���Ϸκ��� ���� ���� �̹����� �ε��ϴ� �Լ�
	HRESULT AngleInit(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� ���� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0, bool isCenterRenderring = false);
	void Render(HDC hdc, int size, int destX, int destY, bool isCenterRenderring);
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring = false);
	void FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring, int size);
	void AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring = false);
	void AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring, int currFrameX, int size);
	// ���� ����
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

