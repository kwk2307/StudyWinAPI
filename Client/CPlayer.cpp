#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CResourceMgr.h"

#include "CCollider.h"
#include "CBlock.h"

CPlayer::CPlayer()
	:m_pTex(nullptr)
{
	m_pTex = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTex", L"Texture\\player.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));
}

CPlayer::~CPlayer()
{
}


void CPlayer::update()
{
	Vec2 vec = GetPos();

	if (KEYCHKCK_HOLD(KEY::A)) {
		vec.x -= float(100 * CTimeMgr::GetInstance()->GetDT());
	}
	if (KEYCHKCK_HOLD(KEY::D)) {
		vec.x += float(100 * CTimeMgr::GetInstance()->GetDT());
	}
	if (KEYCHKCK_HOLD(KEY::W)) {
		vec.y -= float(100 * CTimeMgr::GetInstance()->GetDT());
	}
	if (KEYCHKCK_HOLD(KEY::S)) {
		vec.y += float(100 * CTimeMgr::GetInstance()->GetDT());
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
}

void CPlayer::render(HDC _dc)
{	
	if (GetDead()) {
		delete this;
	}
	else {
		int iWidth = (int)m_pTex->GetWidth();
		int iHeight = (int)m_pTex->GetHeight();
		Vec2 vPos = GetPos();

		BitBlt(_dc,
			int(vPos.x - (float)(iWidth / 2)),
			int(vPos.y - (float)(iHeight / 2)),
			iHeight, iWidth,
			m_pTex->GetDC(),
			0, 0,
			SRCCOPY);

		component_render(_dc);
	}
}




