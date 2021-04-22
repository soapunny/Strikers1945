#pragma once


class Item;
class ItemFactory
{
public:
	virtual Item* CreatItem() = 0;
};

