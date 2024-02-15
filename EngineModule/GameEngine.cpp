#include "Precompiled.h"

bool GameEngine::Init()
{
	_IsInitialized = GetSceneMng().Init();

	return _IsInitialized;
}

