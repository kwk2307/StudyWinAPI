#pragma once

class GameEngine
{
public:
	GameEngine();

public:
	bool Init(std::string& InName);
	bool IsInitailzed() { return _IsInitialized; }

	SceneMng GetSceneMng() { return _SceneMng; }
private:

public:

private:
	bool _IsInitialized;
	SceneMng _SceneMng;
};

