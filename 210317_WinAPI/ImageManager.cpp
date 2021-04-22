#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	//모든 이미지에 대한  메모리 해제가 이루어 진다
	map<string, Image*>::iterator myIt;
	for (myIt = mImageDatas.begin(); myIt != mImageDatas.end(); myIt++)	
	{
		if ((myIt->second))
		{
			(myIt->second)->Release();	//이미지 값들을 먼저 지우고
			delete (myIt->second);
			(myIt->second) = nullptr;
		}
	}
	mImageDatas.clear();				//map 구조 데이터를 지운다

	ReleaseSingleton();
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;

	//맵에 키에 해당하는 데이터가 있으면 추가 생성 없이 이미지 리턴
	image = FindImage(key);
	if (image)
	{
		return image;
	}
	
	//맵에 키에 해당하는 데이터가 없으면 생성 후 맵에 추가한 후 이미지리턴
	image = new Image();
	if (FAILED(image->Init(fileName, width, height, isTransparent, transColor)))
	{
		image->Release();
		delete image;
		
		return nullptr;
	}

	mImageDatas.insert(make_pair(key, image));
	return image;
}

Image* ImageManager::AddAngleImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;

	//맵에 키에 해당하는 데이터가 있으면 추가 생성 없이 이미지 리턴
	image = FindImage(key);
	if (image)
	{
		return image;
	}

	//맵에 키에 해당하는 데이터가 없으면 생성 후 맵에 추가한 후 이미지리턴
	image = new Image();
	if (FAILED(image->AngleInit(fileName, width, height, isTransparent, transColor)))
	{
		image->Release();
		delete image;

		return nullptr;
	}

	mImageDatas.insert(make_pair(key, image));
	return image;
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;

	//맵에 키에 해당하는 데이터가 있으면 추가 생성 없이 이미지 리턴
	image = FindImage(key);
	if (image)
	{
		return image;
	}

	//맵에 키에 해당하는 데이터가 없으면 생성 후 맵에 추가한 후 이미지리턴
	image = new Image();
	if (FAILED(image->Init(fileName, width, height, maxFrameX, maxFrameY, isTransparent, transColor)))
	{
		image->Release();
		delete image;

		return nullptr;
	}

	mImageDatas.insert(make_pair(key, image));
	return image;
}

void ImageManager::DeleteImage(string key)
{
	map<string, Image*>::iterator myIt;	
	myIt = mImageDatas.find(key);

	//없는 경우
	if (myIt == mImageDatas.end())		
	{
		return ;					
	}

	//있는 경우
	(myIt->second)->Release();		//image->Release()
	delete (myIt->second);
	(myIt->second) = nullptr;

	mImageDatas.erase(myIt);
}

Image* ImageManager::FindImage(string key)
{
	map<string, Image*>::iterator myIt;	//map.find()는 iterator를 돌면서 key와 동일한 값이 있는지 확인한다
	myIt = mImageDatas.find(key);		//key에 해당하는 값이 있으면, 그 값이 담겨있는 메모리 주소를 반환한다
	
	if (myIt == mImageDatas.end())		//key에 해당하는 값이 없으면, map의 마지막에 널값에 도달하였다
	{
		return nullptr;
	}

	return myIt->second;				//first(key) second(value)
}
