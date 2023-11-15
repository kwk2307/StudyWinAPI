#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CUI.h"
#include "CButton.h"
#include "CPanel.h"

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

	CPanel* Panel = new CPanel();
	Panel->SetOffset(Vec2(700, 300));
	Panel->SetScale(Vec2(300, 300));
	Panel->SetClickable(true);

	CButton* Btn = new CButton();
	Btn->SetOffset(Vec2(-100, -100));
	Btn->SetScale(Vec2(100, 30));
	Btn->SetClickable(true);

	Panel->SetChild(Btn);

	AddObject(Panel, ObjectType::UI);
	
	CPanel* Panel2 = new CPanel(*Panel);
	Panel2->SetOffset(Vec2(100, 300));

	AddObject(Panel2, ObjectType::UI);

	// 충돌 지정
	// 오브젝트 타입간 충돌 지정
	CCollisionMgr::GetInstance()->CheckGroup(ObjectType::PLAYER, ObjectType::BLOCK);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}


