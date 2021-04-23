#include "ItemPower.h"
#include "CommonFunction.h"
#include "Image.h"
#include "CollisionCheck.h"
HRESULT ItemPower::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;

	currFrameX = 0;
	img = ImageManager::GetSingleton()->FindImage("파워아이템");
	if (img == nullptr)
	{
		MessageBox(g_hWnd, "미사일에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}
	ItemPos.x = dropPos.x;
	ItemPos.y = dropPos.y;
	size = 50;
	isFired = false;/*
	dropPos.x = ItemPos.x;
	dropPos.x = ItemPos.x;*/
	why = true;
	return S_OK;
}

void ItemPower::Update()
{
	//this->collisionCheck
	itemRect = { (LONG)(ItemPos.x - size / 2), (LONG)(ItemPos.y - size / 2), (LONG)(ItemPos.x + size / 2), (LONG)(ItemPos.y + size / 2) };
	collisionCheck->SetItem(this);
	collisionCheck->SetItem(3);

	if (!isFired)
	{
		ItemPos.x = WINSIZE_X / 2;
		ItemPos.y = 0;
	}
	else if (isFired)
	{
		/*moveManager->SetMoveSpeed(moveSpeed);
		moveManager->DoMove(&ItemPos, &angle);*/
		if (why)
		{
			ItemPos.x = dropPos.x;
			ItemPos.y = dropPos.y;
			why = false;
		}
		ItemPos.y++;
	}

	if (ItemPos.x < 0 || ItemPos.y < 0 || ItemPos.x > WINSIZE_X || ItemPos.y > WINSIZE_Y)
	{

		isFired = false;
		why = false;
		//this->collisionCheck->DeletePlayerMissile();
		//fireStep = 0;
	}
	updateCount++;
	if (updateCount >= 5)
	{
		currFrameX = (currFrameX + 1) % 6;
		updateCount = 0;
	}
}

void ItemPower::Render(HDC hdc)
{
	if (isFired)
	{
		//Rectangle(hdc, ItemPos.x-size / 2, ItemPos.y - size / 2, ItemPos.x + size/2, ItemPos.y + size/2);

		img->FrameRender(hdc, ItemPos.x, ItemPos.y, currFrameX, 0, true);
	}

}


void ItemPower::Release()
{
}

void ItemPower::RRRR()
{
}
