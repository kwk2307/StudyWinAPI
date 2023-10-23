#include "pch.h"
#include "CStartScene.h"

#include "CPlayer.h"

void CStartScene::Enter()
{
	CObject* obj = new CPlayer();
	obj->SetPos(Vec2(500.f, 500.f));
	obj->SetScale(Vec2(100.f, 100.f));

	AddObject(obj, ObjectType::PLAYER);

}

void CStartScene::Exit()
{

}
