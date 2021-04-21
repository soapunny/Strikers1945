#include "ItemLife.h"
#include "CommonFunction.h"
#include "Image.h"
#include "NormalMove.h"
#include "CollisionCheck.h"
HRESULT ItemLife::Init(CollisionCheck* collisionCheck, FPOINT position)
{
	img = ImageManager::GetSingleton()->FindImage("라이프아이템");
	if (img == nullptr)
	{
		MessageBox(g_hWnd, "미사일에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}
	ItemPos.x = 100;
	ItemPos.y = 0;
	vMoveInterfaces.resize(MOVETYPE::END_MOVE);
	vMoveInterfaces[MOVETYPE::NORMAL_MOVE] = new NormalMove;	
	moveManager = new MoveManager;
	moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::NORMAL_MOVE]);
	currMoveInterface = vMoveInterfaces[MOVETYPE::NORMAL_MOVE];
	moveSpeed = 500;
	angle = 0;
	size = 50;
	isFired = false;
	dropPos.x = ItemPos.x;
	dropPos.x = ItemPos.x;
	return S_OK;
}	

void ItemLife::Update()
{
	if (isFired)
	{
		moveManager->SetMoveSpeed(moveSpeed);
		moveManager->DoMove(&ItemPos, &angle);
	}
	if (ItemPos.x < 0 || ItemPos.y < 0 || ItemPos.x > WINSIZE_X || ItemPos.y > WINSIZE_Y)
	{
		moveSpeed = 300.0f;
		isFired = false;
		//this->collisionCheck->DeletePlayerMissile();
		//fireStep = 0;
	}
	if (!isFired)
	{
		ItemPos.x = dropPos.x;
		ItemPos.y = dropPos.y;
	}
}

void ItemLife::Render(HDC hdc)
{	
	if (isFired)
	{
		Rectangle(hdc, ItemPos.x - size, ItemPos.y - size, ItemPos.x, ItemPos.y);
	}
	img->Render(hdc, ItemPos.x, ItemPos.y, true);
}


void ItemLife::Release()
{
	for (int i = 0; i < vMoveInterfaces.size(); i++) {
		if (vMoveInterfaces[i])
			SAFE_DELETE(vMoveInterfaces[i]);
	}
}

void ItemLife::RRRR()
{
}
