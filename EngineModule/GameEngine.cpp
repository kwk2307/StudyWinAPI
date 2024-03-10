#include "Precompiled.h"

void GameEngine::Update(float InDeltaSeconds)
{
	GetSceneMng().Update(InDeltaSeconds);
	GetCollisionMng().Update(InDeltaSeconds);
}

bool GameEngine::Init()
{
	SceneMng& sceneMng = GetSceneMng();
	_IsInitialized = sceneMng.Init();

	GetCollisionMng()._FuncPtr = [&sceneMng](UINT InType){
		return  sceneMng.GetCurrentScene(InType);
		};

	GetCollisionMng().CheckGroup(ObjectType::Player, ObjectType::Block);

	return _IsInitialized;
}
