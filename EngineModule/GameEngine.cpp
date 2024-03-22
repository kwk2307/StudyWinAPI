#include "Precompiled.h"

void GameEngine::Update(float InDeltaSeconds)
{
	GetSceneMng().Update(InDeltaSeconds);
	GetCollisionMng().Update(InDeltaSeconds);
}

GameEngine::GameEngine(SceneMngInterface* InSceneMng, CollisionMngInterface* InCollisionMng) :
	_SceneMng(InSceneMng), _CollisionMng(InCollisionMng)
{
}

bool GameEngine::Init(const ScreenPoint& InScreenSize)
{
	_IsInitialized =  GetSceneMng().Init(_CollisionMng);

	GetSceneMng().OnScreenResize(InScreenSize);

	GetCollisionMng().Init(_SceneMng);
	GetCollisionMng().CheckGroup(ObjectType::Player, ObjectType::Block);

	return _IsInitialized;
}