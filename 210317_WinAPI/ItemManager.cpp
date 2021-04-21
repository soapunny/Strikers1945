#include "ItemManager.h"
#include "Image.h"
#include "BossManager.h"
#include "ItemLifeFactory.h"
#include "Item.h"
#include "ItemLife.h"
#include "LeftUpMove.h"

void ItemManager::Init()
{
	dropEnemy = NOTDROP;
	dropPos.x = 0;
	dropPos.y = 0;	
	IsItemIsDrop = true;
	itemFactory = new ItemLifeFactory(); //¾÷
	item = itemFactory->CreatItem();
	item->Init();
}

void ItemManager::Update()
{
	if (IsItemIsDrop)
	{
		item->Update();
	}
}

void ItemManager::Render(HDC hdc)
{
	item->Render(hdc);
}

void ItemManager::Release()
{
	item->Release();
	delete item;
	item = nullptr;
}
