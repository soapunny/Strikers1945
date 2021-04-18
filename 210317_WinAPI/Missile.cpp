#include "Missile.h"
#include "Enemy.h"
#include "Barrel.h"
#include "CommonFunction.h"
#include "Image.h"
#include <math.h>
#include "SkillManager.h"
#include "NormalSkill.h"
#include "CircularSkill.h"
#include "GuidedSkill.h"
#include "PlayerSkill.h"
#include "MeteorSkill.h"
#include "WormSkill.h"
#include "TwoSkill.h"
#include "NotSkill.h"
#include "ZigzagSkill.h"

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
	isFired = false;
	missileType = SKILLTYPE::ZigzagSkillTYPE;
	fireStep = 0;

	// 이미지
	img = ImageManager::GetSingleton()->FindImage("미사일");
	if (img == nullptr)
	{
		MessageBox(g_hWnd, "미사일에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}

	skillManager = new SkillManager();

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
			skillManager->ChangeSkill(new NormalSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::CircularSkillTYPE:
			skillManager->ChangeSkill(new CircularSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::GuidedSkillTYPE:
			skillManager->ChangeSkill(new GuidedSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::PlayerSkillTYPE:
			skillManager->ChangeSkill(new PlayerSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::MeteorSkillTYPE:
			skillManager->ChangeSkill(new MeteorSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::WormSKillTYPE:
			skillManager->ChangeSkill(new WormSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::TwoSKillTYPE:
			skillManager->ChangeSkill(new TwoSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::NotSkillTYPE:
			skillManager->ChangeSkill(new NotSkill());
		case SKILLTYPE::ZigzagSkillTYPE:
			skillManager->ChangeSkill(new ZigzagSkill());
			skillManager->UseSkill(this);
			break;
		case SKILLTYPE::TornadoSkillTYPE:
			skillManager->ChangeSkill(new ZigzagSkill());
			skillManager->UseSkill(this);
			break;
		default:
			break;
		}

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			fireStep = 0;
		}

		if (missileType == SKILLTYPE::PlayerSkillTYPE)
		{
			if( pos.y > GetStartPos().y)
				isFired = false;
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
	}
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
	pos.x = startPos.x;
	pos.y = startPos.y;
}

