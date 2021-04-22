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
	boss3Item = false;

	//vItemFactory.resize(DROPENEMY::ENDROP); //�̰� �� ����/
	//vItemFactory[DROPENEMY::BOSSDROP] = new ItemLifeFactory(); //��

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
	srand(time(NULL));
	vItem[ITEMTABLE::POWERITEM]->Update();
	vItem[ITEMTABLE::LIFEITEM]->Update();
	vItem[ITEMTABLE::BOMBITEM]->Update();
	
	//randomItem = 0;
	for (int i = 0; i < vItem.size(); i++)
	{
		if (!boss1Item)
		{
		//	vItem[i]->SetIsFired(false);
		}
		if (vItem[i])
		{
			if (randomItem == ITEMTABLE::LIFEITEM)
			{
				vItem[ITEMTABLE::LIFEITEM]->SetDropPos(dropPos);
				if (dropEnemy == BOSSDROP && IsItemDrop&&!boss1Item)
				{
					vItem[ITEMTABLE::LIFEITEM]->SetIsFired(true);
					//IsItemDrop = false;
					boss1Item = true;
					break;
				}
			}
			else if (randomItem == ITEMTABLE::BOMBITEM)
			{
				vItem[ITEMTABLE::BOMBITEM]->SetDropPos(dropPos);
				if (dropEnemy == BOSSDROP && IsItemDrop && !boss2Item)
				{
					vItem[ITEMTABLE::BOMBITEM]->SetIsFired(true);
					//IsItemDrop = false;
					boss2Item = true;
					break;
				}
			}
			else if (randomItem == ITEMTABLE::POWERITEM)
			{
				vItem[ITEMTABLE::POWERITEM]->SetDropPos(dropPos);
				if (dropEnemy == BOSSDROP && IsItemDrop && !boss3Item)
				{
					vItem[ITEMTABLE::POWERITEM]->SetIsFired(true);
					//IsItemDrop = false;
					boss3Item = true;
					break;
				}
			}
			
		}
	}

}

void ItemManager::Render(HDC hdc)
{
	for (int i = 0; i < vItem.size(); i++)
		if (vItem[i]) {
			if (randomItem == ITEMTABLE::LIFEITEM)
			{
				if (dropEnemy == BOSSDROP && IsItemDrop)
				{
					vItem[ITEMTABLE::LIFEITEM]->Render(hdc);
					break;
				}
			}
			else if (randomItem == ITEMTABLE::BOMBITEM)
			{
				if (dropEnemy == BOSSDROP && IsItemDrop)
				{
					vItem[ITEMTABLE::BOMBITEM]->Render(hdc);
					break;
				}
			}
			else if (randomItem == ITEMTABLE::POWERITEM)
			{
				if (dropEnemy == BOSSDROP && IsItemDrop)
				{
					vItem[ITEMTABLE::POWERITEM]->Render(hdc);
					break;
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
