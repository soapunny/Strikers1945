#pragma once
#include "config.h"
class Item;
class ItemFactory;

class CollisionCheck;
class ItemManager
{
private:
	/*
	Image* openingImage;
	Image* endingImage;*/
	vector<Item*> vItem;
	vector<ItemFactory*> vItemFactory;
	DROPENEMY dropEnemy;
	FPOINT dropPos;

	bool IsItemDrop;

	bool boss1Item;
	bool boss2Item;
	bool boss3Item;
	enum ITEMTABLE{LIFEITEM,BOMBITEM,POWERITEM,ENDITEM};
	int randomItem;

public:
	//void Render(HDC hdc);
	HRESULT Init() { return S_OK; };
	HRESULT Init(CollisionCheck* collisionCheck);
	void Update();
	void Render(HDC hdc);
	void Release();	
	
	virtual void SetIsItem(bool IsItemIsDrop) { this->IsItemDrop = IsItemIsDrop; };
	inline void SetDropPos(FPOINT dropPos) { this->dropPos = dropPos; }
	inline void SetDropEnemy(DROPENEMY dropEnemy) { this->dropEnemy = dropEnemy; }
	inline void SetRandItem(int a) { this->randomItem = a;}
	
};