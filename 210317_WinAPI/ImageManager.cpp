#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	//��� �̹����� ����  �޸� ������ �̷�� ����
	map<string, Image*>::iterator myIt;
	for (myIt = mImageDatas.begin(); myIt != mImageDatas.end(); myIt++)	
	{
		if ((myIt->second))
		{
			(myIt->second)->Release();	//�̹��� ������ ���� �����
			delete (myIt->second);
			(myIt->second) = nullptr;
		}
	}
	mImageDatas.clear();				//map ���� �����͸� �����

	ReleaseSingleton();
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;

	//�ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰� ���� ���� �̹��� ����
	image = FindImage(key);
	if (image)
	{
		return image;
	}
	
	//�ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ ���� �� �ʿ� �߰��� �� �̹�������
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

	//�ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰� ���� ���� �̹��� ����
	image = FindImage(key);
	if (image)
	{
		return image;
	}

	//�ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ ���� �� �ʿ� �߰��� �� �̹�������
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

	//�ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰� ���� ���� �̹��� ����
	image = FindImage(key);
	if (image)
	{
		return image;
	}

	//�ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ ���� �� �ʿ� �߰��� �� �̹�������
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

	//���� ���
	if (myIt == mImageDatas.end())		
	{
		return ;					
	}

	//�ִ� ���
	(myIt->second)->Release();		//image->Release()
	delete (myIt->second);
	(myIt->second) = nullptr;

	mImageDatas.erase(myIt);
}

Image* ImageManager::FindImage(string key)
{
	map<string, Image*>::iterator myIt;	//map.find()�� iterator�� ���鼭 key�� ������ ���� �ִ��� Ȯ���Ѵ�
	myIt = mImageDatas.find(key);		//key�� �ش��ϴ� ���� ������, �� ���� ����ִ� �޸� �ּҸ� ��ȯ�Ѵ�
	
	if (myIt == mImageDatas.end())		//key�� �ش��ϴ� ���� ������, map�� �������� �ΰ��� �����Ͽ���
	{
		return nullptr;
	}

	return myIt->second;				//first(key) second(value)
}
