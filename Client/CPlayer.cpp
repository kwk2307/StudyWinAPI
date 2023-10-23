#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

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

void CPlayer::render(HDC _hdc)
{
	Rectangle(_hdc,
		int(GetPos().x - GetScale().x / 2),
		int(GetPos().y - GetScale().y / 2),
		int(GetPos().x + GetScale().x / 2),
		int(GetPos().y + GetScale().y / 2)
	);

}

