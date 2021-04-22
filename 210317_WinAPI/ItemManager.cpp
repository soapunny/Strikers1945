#include "ItemManager.h"
#include "Image.h"
#include "BossManager.h"
#include "ItemLifeFactory.h"
#include "Item.h"
#include "ItemLife.h"
#include "ItemBomb.h"
#include "ItemPower.h"
#include "LeftUpMove.h"
#include "CollisionCheck.h"

HRESULT ItemManager::Init(CollisionCheck* collisionCheck)
{
	dropEnemy = NOTDROP;
	dropPos.x = 0;
	dropPos.y = 0;	
	IsItemDrop = true;

	boss1Item = false;
	boss2Item = false;
	enemyItem = false;

	//vItemFactory.resize(DROPENEMY::ENDROP); //이거 왜 있지/
	//vItemFactory[DROPENEMY::BOSSDROP] = new ItemLifeFactory(); //업

	vItem.resize(ITEMTABLE::ENDITEM);
	vItem[ITEMTABLE::LIFEITEM] = new ItemLife;
	vItem[ITEMTABLE::LIFEITEM]->Init(collisionCheck);
	vItem[ITEMTABLE::BOMBITEM] = new ItemBomb;
	vItem[ITEMTABLE::BOMBITEM]->Init(collisionCheck);
	vItem[ITEMTABLE::POWERITEM] = new ItemPower;
	vItem[ITEMTABLE::POWERITEM]->Init(collisionCheck);
	return S_OK;
}

void ItemManager::Update()
{	
	//srand(time(NULL));
	vItem[ITEMTABLE::POWERITEM]->Update();
	vItem[ITEMTABLE::LIFEITEM]->Update();
	vItem[ITEMTABLE::BOMBITEM]->Update();
	
	//randomItem = 0;
	for (int i = 0; i < vItem.size(); i++)
	{		
		if (vItem[i])
		{
			
			if (randomItem == ITEMTABLE::BOMBITEM)
			{
				vItem[ITEMTABLE::BOMBITEM]->SetDropPos(dropPos);
				if (dropEnemy == BOSSONE && IsItemDrop && !boss1Item)
				{
					vItem[ITEMTABLE::BOMBITEM]->SetIsFired(true);
					//IsItemDrop = false;
					boss2Item = true;
					break;
				}
			}
			else if (randomItem == ITEMTABLE::LIFEITEM)
			{
				vItem[ITEMTABLE::LIFEITEM]->SetDropPos(dropPos);
				if (dropEnemy == BOSSTWO && IsItemDrop && !boss2Item)
				{
					vItem[ITEMTABLE::LIFEITEM]->SetIsFired(true);
					//IsItemDrop = false;
					boss1Item = true;
					break;
				}
			}
			else if (randomItem == ITEMTABLE::POWERITEM)
			{
				vItem[ITEMTABLE::POWERITEM]->SetDropPos(dropPos);
				if (dropEnemy == ENEMYDROP && IsItemDrop && !enemyItem)
				{
					vItem[ITEMTABLE::POWERITEM]->SetIsFired(true);
					//IsItemDrop = false;
					enemyItem = true;
					break;
				}
			}
		}
	}
}

void ItemManager::Render(HDC hdc)
{
	for (int i = 0; i < vItem.size(); i++)
	{
		if (vItem[i]) {
			if (randomItem == ITEMTABLE::BOMBITEM)
			{
				if (dropEnemy == BOSSONE && IsItemDrop)
				{
					vItem[ITEMTABLE::BOMBITEM]->Render(hdc);
					break;
				}
			}
			else if (randomItem == ITEMTABLE::LIFEITEM)
			{
				if (dropEnemy == BOSSTWO && IsItemDrop)
				{
					vItem[ITEMTABLE::LIFEITEM]->Render(hdc);
					break;
				}
			}			
			else if (randomItem == ITEMTABLE::POWERITEM)
			{
				if (dropEnemy == ENEMYDROP && IsItemDrop)
				{
					vItem[ITEMTABLE::POWERITEM]->Render(hdc);
					break;
				}
			}

		}
	}
}

void ItemManager::Release()
{
	for (int i = 0; i < vItem.size(); i++)
	{
		SAFE_RELEASE(vItem[i]);
	}
	vItem.clear();
}
