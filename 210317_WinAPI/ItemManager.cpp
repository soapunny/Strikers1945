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
	
	//vItemFactory.resize(DROPENEMY::ENDROP); //이거 왜 있지/
	//vItemFactory[DROPENEMY::BOSSDROP] = new ItemLifeFactory(); //업

	vItem.resize(ITEMTABLE::POWER);
	vItem[ITEMTABLE::LIFE] = new ItemLife;
	vItem[ITEMTABLE::LIFE]->Init();
}

void ItemManager::Update()
{	
	//for (int i = 0; i < ITEMTABLE::POWER; i++)
	{
		vItem[ITEMTABLE::LIFE]->SetDropPos(dropPos);
	}
	//if (dropEnemy ==BOSSDROP&& IsItemIsDrop)
	{
		vItem[ITEMTABLE::LIFE]->SetIsFired(true);
		vItem[ITEMTABLE::LIFE]->Update();
	}
}

void ItemManager::Render(HDC hdc)
{
	//if (dropEnemy == BOSSDROP&& IsItemIsDrop)
	{
		vItem[ITEMTABLE::LIFE]->Render(hdc);
	}
}

void ItemManager::Release()
{
	for (int i = 0; i < ITEMTABLE::POWER; i++)
	{
		SAFE_RELEASE(vItem[i]);
	}
	vItem.clear();
}
