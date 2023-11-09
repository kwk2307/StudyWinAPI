#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResourceMgr.h"

#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CBlock.h"

CPlayer::CPlayer()
{
	CTexture* pTex = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTex", L"Texture\\player.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Anim_Up", pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), 5);
	GetAnimator()->CreateAnim(L"Anim_Down", pTex, Vec2(0.f, 192.f), Vec2(64.f, 64.f), 5);
	GetAnimator()->CreateAnim(L"Anim_Left", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), 5);
	GetAnimator()->CreateAnim(L"Anim_Right", pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), 5);

	GetAnimator()->SetCurAnim(L"Anim_Down");
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vec = GetPos();

	if (KEYCHKCK_HOLD(KEY::A)) {
		vec.x -= float(100 * CTimeMgr::GetInstance()->GetDT());
		GetAnimator()->SetCurAnim(L"Anim_Left");
	}
	if (KEYCHKCK_HOLD(KEY::D)) {
		vec.x += float(100 * CTimeMgr::GetInstance()->GetDT());
		GetAnimator()->SetCurAnim(L"Anim_Right");
	}
	if (KEYCHKCK_HOLD(KEY::W)) {
		vec.y -= float(100 * CTimeMgr::GetInstance()->GetDT());
		GetAnimator()->SetCurAnim(L"Anim_Up");
	}
	if (KEYCHKCK_HOLD(KEY::S)) {
		vec.y += float(100 * CTimeMgr::GetInstance()->GetDT());
		GetAnimator()->SetCurAnim(L"Anim_Down");
	}
	
	if (KEYCHKCK_TAP(KEY::SPACE)) {
	//
		CBlock* block = new CBlock();
		block->SetScale(Vec2(100.f, 100.f));
		block->SetPos(Vec2(300.f, 300.f));
		CreateObject(block, ObjectType::BLOCK);
	}

	if (KEYCHKCK_TAP(KEY::ENTER)) {
		ChangeScene(SceneType::STAGE01);
	}

	SetPos(vec);

	if (GetAnimator() != nullptr) {
		GetAnimator()->update();
	}
}

void CPlayer::render(HDC _dc)
{	
	if (GetDead()) {
		delete this;
	}
	else {

		if (GetAnimator() != nullptr) {
			GetAnimator()->render(_dc);
		}
		component_render(_dc);
	}
}




