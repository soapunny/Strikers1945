 #include "Image.h"
#include "wingdi.h"			//���� ȸ��

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC                                                                                              (hdc);
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

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent/* = FALSE*/, COLORREF transColor/* = FALSE*/)
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

    //����ִ� ���ĺ��� dc �����
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldhBlendBit =
        (HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

    //����ִ� temp ���� dc �����
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

HRESULT Image::AngleInit(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    //�̹��� ���� �ʱ�ȭ
    HDC hdc = GetDC(g_hWnd);
    int reSize = (int)ceil(sqrt(width * width + height * height));

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    
    imageInfo->hAngleBitmap[0] = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hAngleBitmap[1] = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hAngleOldBit[0] = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->hAngleOldBit[1] = (HBITMAP)SelectObject(imageInfo->hMemDC,  imageInfo->hBitmap);

    imageInfo->width = width;   //ȸ�� �� �̹��� ũ��
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    //��� �̹��� �����ͼ� ������, ����ִ� DC(hTempDC) �����
    imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hTempBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hTempBrush = CreateSolidBrush(RGB(255, 0, 255));
    DeleteObject(SelectObject(imageInfo->hTempDC, imageInfo->hTempBitmap));

    //���� ȸ�� (2���� �������)
    XFORM xForm[2] = { 0.0f };
    XFORM xOldForm;
    //135��
    xForm[0].eM11 = (float)cos(3 * (PI / 4));   xForm[0].eM12 = (float)sin(3 * (PI / 4));
    xForm[0].eM21 = (float)-sin(3 * (PI / 4));  xForm[0].eM22 = (float)cos(3 * (PI / 4));
    //xForm[0].eDx = ??;   xForm[0].eDy = ??;  
    //45��
    xForm[1].eM11 = (float)cos(PI / 4);   xForm[1].eM12 = (float)sin(PI / 4);
    xForm[1].eM21 = (float)-sin(PI / 4);  xForm[1].eM22 = (float)cos(PI / 4);
    //xForm[1].eDx = ? ? ;   xForm[1].eDy = ? ? ;

    for (int i = 0; i < 2; i++)
    {
        //���� ȸ�� �̹��� ������, ����ִ� DC(hTempDC) �����
        //imageInfo->hAngleDC[i] = CreateCompatibleDC()
        //SetGraphicsMode(imageInfo->hMemDC, GM_ADVANCED);
        SetWorldTransform(imageInfo->hMemDC, &xForm[i]);
    }
    DeleteObject(imageInfo->hAngleTempDC);
    DeleteObject(imageInfo->hAngleTempBitmap);
    DeleteObject(imageInfo->hAngleTempBrush);


    imageInfo->hAngleDC[0] = CreateCompatibleDC(imageInfo->hTempDC);
    imageInfo->hAngleDC[1] = CreateCompatibleDC(imageInfo->hTempDC);
    imageInfo->hAngleDC[1] = CreateCompatibleDC(imageInfo->hTempDC);



    //ȸ�� �� �̹��� ũ�� ���� ����
    imageInfo->width = reSize;
    imageInfo->height = reSize;

    // ������
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

    return S_OK;;
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

    //����ִ� ���ĺ��� dc �����
    imageInfo->hBlendDC = CreateCompatibleDC(hdc);
    imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldhBlendBit =
        (HBITMAP)SelectObject(imageInfo->hBlendDC, imageInfo->hBlendBitmap);

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
    this->blendFunc.SourceConstantAlpha = 50;

    return S_OK;
}

//������ ������ �ʿ� ���� �� ���
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
        // Ư�� ������ ���� �����ϴ� �Լ�
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
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                // ���� ������ DC
            x, y,       // ���� ���� ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );     
    }

  
}

void Image::Render(HDC hdc, int size, int destX, int destY, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;

    if (isCenterRenderring)
    {
        x -= (size / 2);
        y -= (size / 2);

        //x -= (imageInfo->width * (size / imageInfo->width)) / 2;
        //y -= (imageInfo->height * (size / imageInfo->height)) / 2;
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,
            x, y,
            size, size,
            //imageInfo->width * (size / imageInfo->width), imageInfo->height * (size / imageInfo->height),

            imageInfo->hMemDC,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        // bitmap �� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                // ���� ������ DC
            x, y,       // ���� ���� ��ġ
            imageInfo->width,   // �������� ����� ����ũ��
            imageInfo->height,  // �������� ����� ����ũ��
            imageInfo->hMemDC,  // ���� DC
            0, 0,               // �������� ���� ���� ��ġ
            SRCCOPY             // ���� �ɼ�
        );
    }
}

//������ ������ �ʿ� ���� �� ���
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
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,                                            // ������ DC

            x, y,                                           // ������ �ٿ��ִ� ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight,  // ������ �ٿ��ִ� ũ��

            imageInfo->hMemDC,                              // ��� DC

            imageInfo->frameWidth * imageInfo->currFrameX,  // ���� ���� X ��ġ
            imageInfo->frameHeight * imageInfo->currFrameY, // ���� ���� Y ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight,  // ���� ���� ũ��

            transColor                                      // ������ ����
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

void Image::FrameRender(HDC hdc, int destX, int destY, int currFrameX, int currFrameY, bool isCenterRenderring, int size)
{
    imageInfo->currFrameX = currFrameX;
    imageInfo->currFrameY = currFrameY;

    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x -= (size / 2);
        y -= (size / 2);
    }

    if (isTransparent)
    {
        // Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,                                            // ������ DC

            x, y,                                           // ������ �ٿ��ִ� ��ġ
            size, size,  // ������ �ٿ��ִ� ũ��

            imageInfo->hMemDC,                              // ��� DC

            imageInfo->frameWidth * imageInfo->currFrameX,  // ���� ���� X ��ġ
            imageInfo->frameHeight * imageInfo->currFrameY, // ���� ���� Y ��ġ
            imageInfo->frameWidth, imageInfo->frameHeight,  // ���� ���� ũ��

            transColor                                      // ������ ����
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
    1. ������ũ ȿ��
    2. �� ȿ��
    3. ��Ȧ ȿ��
    4. ���� ȿ��
    */

    // ����DC(hdc)�� �׷��� �ִ� ����(���)�� (����� �ִ� �ӽ�) BlendDC�� ����
    BitBlt(
        imageInfo->hBlendDC,                 // ���� ������ DC
        0, 0,                                // ���� ���� ��ġ
        imageInfo->width,                    // �������� ����� ����ũ��
        imageInfo->height,                   // �������� ����� ����ũ��
        hdc,                                 // ���� DC
        x, y,                                // �������� ���� ���� ��ġ
        SRCCOPY                              // ���� �ɼ�
    );

    // ����� �̹��� hMemDC�� ����(���ּ� �̹���)�� ������ ����(����Ÿ)�� �����ϸ鼭 BlendDC�� ����
    GdiTransparentBlt(
        imageInfo->hBlendDC, 
        0, 0,
        imageInfo->width, imageInfo->height,
        imageInfo->hMemDC,
        0, 0,
        imageInfo->width, imageInfo->height,
        transColor
    );
    
    // BlendDC�� ����DC(hdc)�� �׷��ִ� �������� ���ĺ��� �����Ű��
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

//void Image::AlphaRender(HDC hdc, int destX, int destY, bool isCenterRenderring, int currFrameX, int size)
//{
//    imageInfo->currFrameX = currFrameX;
//    imageInfo->currFrameY = 0;
//    int x = destX;
//    int y = destY;
//    if (isCenterRenderring)
//    {
//        x -= (size / 2);
//        y -= (size / 2);
//    }
//
//    /*
//    1. ������ũ ȿ��
//    2. �� ȿ��
//    3. ��Ȧ ȿ��
//    4. ���� ȿ��
//    */
//
//    // ����DC(hdc)�� �׷��� �ִ� ����(���)�� (����� �ִ� �ӽ�) BlendDC�� ����
//    BitBlt(
//        imageInfo->hBlendDC,                 // ���� ������ DC
//        0, 0,                               // ���� ���� ��ġ
//        size,size,
//
//
//        hdc,
//        destX,destY,                            // �������� ���� ���� ��ġ
//        SRCCOPY                              // ���� �ɼ�
//    );
//
//    // ����� �̹��� hMemDC�� ����(���ּ� �̹���)�� ������ ����(����Ÿ)�� �����ϸ鼭 BlendDC�� ����
//    GdiTransparentBlt(
//        imageInfo->hBlendDC,
//        0, 0,
//        size, size,
//
//
//        imageInfo->hMemDC,
//        imageInfo->frameWidth * currFrameX,      // 
//        imageInfo->frameHeight * 0,
//        imageInfo->frameWidth,
//        imageInfo->frameHeight,
//        transColor
//    );
//    
//    // BlendDC�� ����DC(hdc)�� �׷��ִ� �������� ���ĺ��� �����Ű��
//    AlphaBlend(
//        hdc,
//        x, y,
//        size, size,
//
//
//        imageInfo->hBlendDC,        
//        0,0,
//        size, size,
//        blendFunc
//    );  //BLENDFUNCTION()
//
//}

//�̹��� angle ��ŭ ȸ�� ��ų �� ���
void Image::AngleRender(HDC hdc, int destX, int destY, float angle, bool isCenterRenderring)
{
    int x = destX;
    int y = destY;
    if (isCenterRenderring)
    {
        x -= (imageInfo->width) / 2;
        y -= (imageInfo->height) / 2;
    }

    //��� �̹��� �����ͼ� ������, ����ִ� DC(hTempDC) �����
    if (!imageInfo->hTempDC)
    {
        reSize = (int)ceil(sqrt(imageInfo->width * imageInfo->width + imageInfo->height * imageInfo->height));
        imageInfo->hTempDC = CreateCompatibleDC(imageInfo->hMemDC);
        imageInfo->hTempBitmap = CreateCompatibleBitmap(imageInfo->hMemDC, reSize, reSize);
        imageInfo->hTempBrush = CreateSolidBrush(transColor);
        DeleteObject(SelectObject(imageInfo->hTempDC, imageInfo->hTempBitmap));
        DeleteObject(SelectObject(imageInfo->hTempDC, imageInfo->hTempBrush));
        PatBlt(imageInfo->hTempDC, 0, 0, reSize, reSize, PATCOPY);
    }

    // �־��� ���� �����ϱ�
    XFORM xForm = { 0.0f };
    xForm.eM11 = (float)cos(angle); xForm.eM12 = (float)sin(angle);
    xForm.eM21 = (float)-sin(angle); xForm.eM22 = (float)cos(angle);
    xForm.eDx = (reSize - (float)cos(angle)* imageInfo->width + (float)sin(angle) * imageInfo->height)/2;    
    xForm.eDy = (reSize - (float)cos(angle) * imageInfo->height - (float)sin(angle) * imageInfo->width) / 2;
    XFORM xOldForm = { 0.0f };
    SetGraphicsMode(imageInfo->hTempDC, GM_ADVANCED);
    SetWorldTransform(imageInfo->hTempDC, &xForm);

    //����� ũ��� �÷��ֱ�
    GetWorldTransform(imageInfo->hTempDC, &xOldForm);
    StretchBlt(
        imageInfo->hTempDC,
        0, 0,
        imageInfo->width, imageInfo->height,
        imageInfo->hMemDC,
        imageInfo->width, imageInfo->height,
        0,0,
        SRCCOPY
    );
    SetWorldTransform(imageInfo->hTempDC, &xOldForm);

    //�� ����
    if(isTransparent)
    {
        // ����� �̹��� hMemDC�� ����(���ּ� �̹���)�� ������ ����(����Ÿ)�� �����ϸ鼭 BlendDC�� ����
        GdiTransparentBlt(
            hdc,
            x, y,
            reSize, reSize,
            imageInfo->hTempDC,
            0, 0,
            reSize, reSize,
            transColor
        );
    }

    //���� DC(hdc) ���� ���� ���߰�+�����ٰ� �˷��ֱ�
    SetGraphicsMode(hdc, GM_COMPATIBLE);
}

void Image::Release()
{
    if (imageInfo)
    {
        if(imageInfo->hMemDC){
            SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
            DeleteObject(imageInfo->hBitmap);
            DeleteDC(imageInfo->hMemDC);
        }


        if (imageInfo->hBlendDC) {
            SelectObject(imageInfo->hBlendDC, imageInfo->hOldhBlendBit);
            DeleteObject(imageInfo->hBlendBitmap);
            DeleteDC(imageInfo->hBlendDC);
        }

        delete imageInfo;
        imageInfo = nullptr;
    }
}
