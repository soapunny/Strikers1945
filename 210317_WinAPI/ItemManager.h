#pragma once
#include "ItemObserver.h"
#include "config.h"
class Item;
class ItemFactory;
class BossManager;
class ItemManager : public ItemObserver
{
private:
	/*
	Image* openingImage;
	Image* endingImage;*/
	vector<Item*> vItem;
	vector<ItemFactory*> vItemFactory;
	DROPENEMY dropEnemy;
	FPOINT dropPos;
	BossManager* bossManager;
	bool IsItemIsDrop;
	enum ITEMTABLE{LIFE,BOMB,POWER};
	

public:
	//void Render(HDC hdc);
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();	
	virtual void SetDropNotify(DROPENEMY dropItem) 	{ this->dropEnemy = dropItem; };
	virtual void SetDropPos(FPOINT pos) { this->dropPos = dropPos; };
	virtual void SetIsItem(bool IsItemIsDrop) { this->IsItemIsDrop = IsItemIsDrop; };
};