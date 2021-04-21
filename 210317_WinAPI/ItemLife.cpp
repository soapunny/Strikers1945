#include "ItemLife.h"
#include "CommonFunction.h"
#include "Image.h"
#include "NormalMove.h"
#include "CommonFunction.h"
HRESULT ItemLife::Init()
{
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

	return S_OK;
}	

void ItemLife::Update()
{
	moveManager->SetMoveSpeed(moveSpeed);
	moveManager->DoMove(&ItemPos, &angle);	
}

void ItemLife::Render(HDC hdc)
{	
	Rectangle(hdc, ItemPos.x - size, ItemPos.y - size, ItemPos.x, ItemPos.y);
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
