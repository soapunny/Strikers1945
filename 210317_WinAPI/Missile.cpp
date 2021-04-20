#include "Missile.h"
#include "Enemy.h"
#include "Barrel.h"
#include "CommonFunction.h"
#include "Image.h"
#include <math.h>
#include "SkillManager.h"
#include "NormalSkill.h"
#include "FallingKnivesSkill.h"
#include "FireworkSkill.h"
#include "CircularSkill.h"
#include "GuidedSkill.h"
#include "PlayerSkill.h"
#include "MeteorSkill.h"
#include "WormSkill.h"
#include "TwoSkill.h"
#include "NotSkill.h"
#include "ZigzagSkill.h"
#include "TornadoSkill.h"
#include "CollisionCheck.h"

HRESULT Missile::Init(CollisionCheck* collisionCheck, FPOINT position)
{
	this->collisionCheck = collisionCheck;

	startPos = position;
	pos = {-100, -100};
	// (속력 = 거리 / 시간)
	// moveSpeed * (elapsedTime / moveTime) = moveSpeed / (moveTime / elapsedTime)
	moveTime = 2.0f;	//10초 동안
	moveSpeed = 300 ;	//500을 이동하고 싶다

	size = 20;
	shape = { 0, 0, 0, 0 };
	damage = 500;
	isFired = false;

	missileType = SKILLTYPE::FIREWORK_TYPE;

	vSkillInterfaces.resize(SKILLTYPE::END_TYPE);
	vSkillInterfaces[SKILLTYPE::CircularSkill_TYPE] = new CircularSkill;
	vSkillInterfaces[SKILLTYPE::FallingKnives_TYPE] = new FallingKnivesSkill;
	vSkillInterfaces[SKILLTYPE::FIREWORK_TYPE]		= new FireworkSkill;
	vSkillInterfaces[SKILLTYPE::Guided_Skill_TYPE]	= new GuidedSkill;
	vSkillInterfaces[SKILLTYPE::MeteorSkill_TYPE]	= new MeteorSkill;
	vSkillInterfaces[SKILLTYPE::NormalSkill_TYPE]	= new NormalSkill;
	vSkillInterfaces[SKILLTYPE::NotSkill_TYPE]		= new NotSkill;
	vSkillInterfaces[SKILLTYPE::PlayerSkill_TYPE]	= new PlayerSkill;
	vSkillInterfaces[SKILLTYPE::TornadoSkill_TYPE]	= new TornadoSkill;
	vSkillInterfaces[SKILLTYPE::TwoSKill_TYPE]		= new TwoSkill;
	vSkillInterfaces[SKILLTYPE::WormSKill_TYPE]		= new WormSkill;
	vSkillInterfaces[SKILLTYPE::ZigzagSkill_TYPE]	= new ZigzagSkill;

	skillManager = new SkillManager();
	lpCurrSkill = vSkillInterfaces[SKILLTYPE::NormalSkill_TYPE];
	skillManager->ChangeSkill(lpCurrSkill);

	fireStep = 0;

	ownerType = OWNERTYPE::ENEMY;

	// 이미지
	img = ImageManager::GetSingleton()->FindImage("적 미사일");
	if (img == nullptr)
	{
		MessageBox(g_hWnd, "미사일에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}


    return S_OK;
}

void Missile::Release()
{
	SAFE_DELETE(skillManager);
	for (int i = 0; i < vSkillInterfaces.size(); i++) {
		if (vSkillInterfaces[i])
		{
			SAFE_DELETE(vSkillInterfaces[i]);
		}
	}
	vSkillInterfaces.clear();
}

void Missile::Update()
{
	//장전 시킨 미사일 타입의, 발사 스킬 가져오기
	if (isFired)
	{
		switch (missileType)
		{
		case SKILLTYPE::NormalSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::NormalSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::NormalSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;

		case SKILLTYPE::FallingKnives_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::FallingKnives_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::FallingKnives_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;

		case SKILLTYPE::FIREWORK_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::FIREWORK_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::FIREWORK_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::CircularSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::CircularSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::CircularSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::Guided_Skill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::Guided_Skill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::Guided_Skill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::PlayerSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::PlayerSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::PlayerSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::MeteorSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::MeteorSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::MeteorSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::WormSKill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::WormSKill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::WormSKill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::TwoSKill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::TwoSKill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::TwoSKill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::NotSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::NotSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::NotSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
		case SKILLTYPE::ZigzagSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::ZigzagSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::ZigzagSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		case SKILLTYPE::TornadoSkill_TYPE:
			if (lpCurrSkill != vSkillInterfaces[SKILLTYPE::TornadoSkill_TYPE]) {
				lpCurrSkill = vSkillInterfaces[SKILLTYPE::TornadoSkill_TYPE];
				skillManager->ChangeSkill(lpCurrSkill);
			}
			break;
		default:
			break;
		}
		skillManager->UseSkill(this, lpTargetPos);

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			moveSpeed = 300.0f;
			skillManager->Renew();
			isFired = false;
			this->collisionCheck->DeletePlayerMissile(this);
			fireStep = 0;
		}

		if (missileType == SKILLTYPE::PlayerSkill_TYPE)
		{
			if (pos.y > GetPlayerPos().y)
			{
				isFired = false;
				this->collisionCheck->DeletePlayerMissile(this);
			}
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
		//충돌 박스
		if (ownerType == OWNERTYPE::PLAYER)
			playerMissileRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + size), (LONG)(pos.y + size) };
		else if (ownerType == OWNERTYPE::ENEMY || ownerType == OWNERTYPE::BOSS)
			enemyMissileRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + size), (LONG)(pos.y + size) };

		if(ownerType == OWNERTYPE::PLAYER)
			img = ImageManager::GetSingleton()->FindImage("플레이어 미사일");
		else if(ownerType == OWNERTYPE::ENEMY || ownerType == OWNERTYPE::BOSS)
			img = ImageManager::GetSingleton()->FindImage("적 미사일");
		img->Render(hdc, pos.x, pos.y, true);
	}
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
	pos.x = startPos.x;
	pos.y = startPos.y;
}

