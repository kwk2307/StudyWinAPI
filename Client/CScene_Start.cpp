#include "pch.h"
#include "CScene_Start.h"
#include "CPlayer.h"

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
}

void CScene_Start::Exit()
{

}
