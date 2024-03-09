#include "Precompiled.h"

bool GameEngine::Init()
{
	_IsInitialized = GetSceneMng().Init();

	SceneMng scene;

	_SceneMng.Init();

	return _IsInitialized;
}

const std::vector<std::unique_ptr<Object>>& GameEngine::GetCurrentScene(UINT InType)
{
	return _SceneMng.GetCurrentScene(InType);
}

