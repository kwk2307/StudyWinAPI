#include "PreComplied.h"

bool GameEngine::Init(std::string& SceneName){

	if (_SceneName == SceneName) {
		return _IsInitialized;
	}

	_SceneName = SceneName;
	
	//_Scene =
	return _IsInitialized;
}
