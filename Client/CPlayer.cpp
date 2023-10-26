#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CTexture.h"
#include "CResourceMgr.h"

#include "CCollider.h"

CPlayer::CPlayer()
	:m_pTex(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	m_pTex = CResourceMgr::GetInstance()->LoadTexture(L"PlayerTex", L"Texture\\player.bmp");
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
	
	SetPos(vec);
}

void CPlayer::render(HDC _dc)
{
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


