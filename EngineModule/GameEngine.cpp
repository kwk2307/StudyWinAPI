#include "Precompiled.h"

bool GameEngine::Init(std::string& InName)
{
	GetSceneMng().Init();
	return _IsInitialized;
}

