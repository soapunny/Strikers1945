#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include <math.h>
#include "SkillManager.h"
#include "NormalSkill.h"
#include "FallingKnivesSkill.h"
#include "FireworkSkill.h"

HRESULT Missile::Init(FPOINT position)
{
	startPos = position;
	pos = {-100, -100};
	// (속력 = 거리 / 시간)
	// moveSpeed * (elapsedTime / moveTime) = moveSpeed / (moveTime / elapsedTime)
	moveTime = 2.0f;	//10초 동안
	moveSpeed = 500;	//500을 이동하고 싶다

	size = 25;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = SKILLTYPE::FIREWORKTYPE;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;


	// 이미지
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");
	if (img == nullptr)
	{
		MessageBox(g_hWnd, "enemy missile 에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}

	skillManager = new SkillManager();
	skillManager->ChangeSkill(new FireworkSkill());

    return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	//장전 시킨 미사일 타입의, 발사 스킬 가져오기
	if (isFired)
	{
		switch (missileType)
		{
		case SKILLTYPE::NormalSkillTYPE:
			//skillManager->ChangeSkill(new NormalSkill());
			break;

		case SKILLTYPE::FallingKnivesTYPE:
			break;

		case SKILLTYPE::FIREWORKTYPE:
			break;
		default:
			break;
		}
		skillManager->UseSkill(this, lpTargetPos);

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			moveSpeed = 500.0f;
			skillManager->Renew();
			isFired = false;
			fireStep = 0;
		}
	}

	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
}

void Missile::Render(HDC hdc)
{
	if (isFired)
	{
		img->Render(hdc, pos.x, pos.y, true);
		//img->Render(hdc, pos.x - (size / 2), pos.y - (size / 2));
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
	pos.x = startPos.x;
	pos.y = startPos.y;
}

