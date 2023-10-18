#include "pch.h"
#include "CStartScene.h"

#include "CObject.h"
void CStartScene::Enter()
{
	CObject* obj = new CObject;

	GetVecObject(ObjectType::DEFAULT).push_back(obj);
}

void CStartScene::Exit()
{
}
