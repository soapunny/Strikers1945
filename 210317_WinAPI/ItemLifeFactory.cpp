#include "ItemLifeFactory.h"
#include "ItemLife.h"

Item* ItemLifeFactory::CreatItem()
{
	return new ItemLife;
}
