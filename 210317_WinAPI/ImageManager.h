#pragma once
#include "config.h"
#include "Singleton.h"

class Image;
class CollisionCheck;
class ImageManager: public Singleton<ImageManager>
{
private:
	// map 함수는 Key(string)를 사용하여 내부적으로 자동 정렬한 후
	// Key(string)로 뒤에있는 Value(Image*)를 빠르게 찾아준다
	map<string, Image*> mImageDatas;	

public:
	HRESULT Init();

	void Release();

	//정적 이미지
	Image* AddImage(string key, const char* fileName,
		int width, int height, 
		bool isTransparent = FALSE, COLORREF transColor = FALSE);
	//정적 각도 이미지
	Image* AddAngleImage(string key, const char* fileName,
		int width, int height,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);
	//프레임 있는 동적 이미지
	Image* AddImage(string key, const char* fileName,
		int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void DeleteImage(string key);
	Image* FindImage(string key);
};

