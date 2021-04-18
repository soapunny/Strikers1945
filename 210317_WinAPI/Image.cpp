#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = 
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = FALSE;
    this->transColor = FALSE;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
    bool isTransparent/* = FALSE*/, COLORREF transColor/* = FALSE*/)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = 
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);

    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    //비어있는 알파블랜드 dc 만들기
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldhBlendBit =
        (HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

    //비어있는 temp 블랜드 dc 만들기
    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBitmap = CreateCompatibleBitmap(hdc, width*2, height);
    imageInfo->hOldhTempBit =
        (HBITMAP)SelectObject(imageInfo->hTempDC, imageInfo->hTempBitmap);
    k = 0.0f;
    a = 0.01f;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    this->blendFunc.AlphaFormat = 0;
    this->blendFunc.BlendFlags = 0;
    this->blendFunc.BlendOp = AC_SRC_OVER;
    this->blendFunc.SourceConstantAlpha = 255;

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap =
        (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

//프레임 조절이 필요 없을 때 사용
void Image::Render(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x -= (imageInfo->width) / 2;
        y -= (imageInfo->height) / 2;
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,
            x, y,
            imageInfo->width, imageInfo->height,

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap 에 있는 이미지 정보를 다른 비트맵에 복사
        BitBlt(
            hdc,                // 복사 목적지 DC
            x, y,       // 복사 시작 위치
            imageInfo->width,   // 원본에서 복사될 가로크기
            imageInfo->height,  // 원본에서 복사될 세로크기
            imageInfo->hMemDC,  // 원본 DC
            0, 0,               // 원본에서 복사 시작 위치
            SRCCOPY             // 복사 옵션
        );     
    }

  
}

//프레임 조절이 필요 있을 때 사용
void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x -= (imageInfo->frameWidth) / 2;
        y -= (imageInfo->frameHeight) / 2;
    }

    if (isTransparent)
    {
        // 특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,                                            // 목적지 DC

            x, y,                                           // 윈도우 붙여넣는 위치
            imageInfo->frameWidth, imageInfo->frameHeight,  // 윈도우 붙여넣는 크기

            imageInfo->hMemDC,                              // 출발 DC

            imageInfo->frameWidth * imageInfo->currFrameX,  // 원본 복사 X 위치
            imageInfo->frameHeight * imageInfo->currFrameY, // 원본 복사 Y 위치
            imageInfo->frameWidth, imageInfo->frameHeight,  // 원본 복사 크기

            transColor                                      // 제외할 색상
        );
    }
    else
    {
        BitBlt(
            hdc,
            x, y,
            imageInfo->frameWidth,
            imageInfo->frameHeight,
            imageInfo->hMemDC,
            (imageInfo->frameWidth) * (imageInfo->currFrameX),
            (imageInfo->frameHeight) * (imageInfo->currFrameY),
            SRCCOPY
        );
    }
}

void Image::AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x -= (imageInfo->width) / 2;
        y -= (imageInfo->height) / 2;
    }
    
    /*
    1. 모자이크 효과
    2. 블러 효과
    3. 블랙홀 효과
    4. 퍼즐 효과
    */

    // 원본DC(hdc)에 그려져 있는 내용(배경)을 (비어져 있는 임시) BlendDC에 복사
    BitBlt(
        imageInfo->hBlendDC,                 // 복사 목적지 DC
        0, 0,                                // 복사 시작 위치
        imageInfo->width,                    // 원본에서 복사될 가로크기
        imageInfo->height,                   // 원본에서 복사될 세로크기
        hdc,                                 // 원본 DC
        x, y,                                // 원본에서 복사 시작 위치
        SRCCOPY                              // 복사 옵션
    );

    // 출력할 이미지 hMemDC의 내용(우주선 이미지)을 지정한 색상(마젠타)을 제외하면서 BlendDC에 복사
    GdiTransparentBlt(
        imageInfo->hBlendDC, 
        0, 0,
        imageInfo->width, imageInfo->height,
        imageInfo->hMemDC,
        0, 0,
        imageInfo->width, imageInfo->height,
        transColor
    );
    
    // BlendDC를 원본DC(hdc)에 그려주는 과정에서 알파블랜드 적용시키기
    AlphaBlend(
        hdc, 
        x, y,
        imageInfo->width, imageInfo->height, 
        imageInfo->hBlendDC,
        0, 0, 
        imageInfo->width, imageInfo->height, 
        blendFunc);  //BLENDFUNCTION()
    

    //sin
    /*BitBlt(
        imageInfo->hTempDC,
        0, 0,
        imageInfo->width*2, imageInfo->height,
        hdc,
        x, y,
        SRCCOPY
    );

    if(k >= 0.5f)
        a= -0.03f;
    if (k <= -0.5f)
        a = 0.03f;
    k += a;

    for (int y = 0; y < imageInfo->height; y++)
    {
        for (int x = 0; x < imageInfo->width; x++)
        {
            float pi = 3.142092;
            float d = k * sin(2 * pi * (float)y / imageInfo->height) * imageInfo->height/2;

            //if (x + d > 0 && x + d < imageInfo->width)
            {
                BitBlt(
                    imageInfo->hTempDC,
                    x + d+ imageInfo->width/4, y,
                    1, 1,
                    imageInfo->hBlendDC,
                    x, y,
                    SRCCOPY
                );
            }
        }
    }

    BitBlt(
        hdc,
        x, y,
        imageInfo->width*2,
        imageInfo->height,
        imageInfo->hTempDC,
        0, 0,
        SRCCOPY
    );*/
  
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);

        delete imageInfo;
        imageInfo = nullptr;
    }
}
