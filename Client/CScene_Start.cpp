#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"

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

	CObject* obj2 = new CPlayer(*(CPlayer*)obj);
	obj2->SetPos(Vec2(600.f, 500.f));

	AddObject(obj2, ObjectType::PLAYER);

	// 충돌 지정
	// 오브젝트 타입간 충돌 지정
	CCollisionMgr::GetInstance()->CheckGroup(ObjectType::PLAYER, ObjectType::BLOCK);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}


