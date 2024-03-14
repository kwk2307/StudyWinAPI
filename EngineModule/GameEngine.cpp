#include "Precompiled.h"

void GameEngine::Update(float InDeltaSeconds)
{
	GetSceneMng().Update(InDeltaSeconds);
	GetCollisionMng().Update(InDeltaSeconds);
}

GameEngine::GameEngine(SceneMng* InSceneMng, CollisionMng* InCollisionMng):
	_SceneMng(InSceneMng),_CollisionMng(InCollisionMng)
{

}

bool GameEngine::Init()
{
	GetSceneMng().Init(_CollisionMng);
	GetCollisionMng().Init(_SceneMng);

	GetCollisionMng().CheckGroup(ObjectType::Player, ObjectType::Block);

	return true;
}
