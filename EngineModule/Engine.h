#pragma once

class Engine
{
public:
	Engine() = default;

public:
	bool Init(std::string& InName);
	bool IsInitailzed();

	SceneMng GetSceneMng() { return _SceneMng; }
private:

public:

private:
	bool _IsInitialized;
	SceneMng _SceneMng;
};

