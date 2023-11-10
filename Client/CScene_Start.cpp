#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CUI.h"

#include "CCollisionMgr.h"

CScene_Start::CScene_Start()
{}

CScene_Start::~CScene_Start()
{}

void CScene_Start::Enter()
{

	CObject* obj = new CPlayer();
	obj->SetPos(Vec2(500.f, 500.f));
	obj->SetScale(Vec2(100.f, 100.f));

	AddObject(obj, ObjectType::PLAYER);
	
	// 카메라 위치 지정
	CCamera::GetInstance()->SetObj(obj);
	

	CUI* UI = new CUI();
	UI->SetOffset(Vec2(700, 300));
	UI->SetScale(Vec2(300, 300));

	CUI* UI2 = new CUI();
	UI2->SetOffset(Vec2(-300, -100));
	UI2->SetScale(Vec2(100, 30));
	
	UI->SetChild(UI2);

	AddObject(UI, ObjectType::UI);

	// 충돌 지정
	// 오브젝트 타입간 충돌 지정
	CCollisionMgr::GetInstance()->CheckGroup(ObjectType::PLAYER, ObjectType::BLOCK);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}


