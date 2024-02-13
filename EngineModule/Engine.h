#pragma once
class Engine
{
public:
	Engine() = default;

public:
	bool Init(std::string& InName){
		_IsInitialized = true;
		return _IsInitialized;
	}
	;
	bool IsInitailzed() { return _IsInitialized; }

	SceneMng GetSceneMng() { return _SceneMng; }
private:

public:

private:
	bool _IsInitialized;
	SceneMng _SceneMng;
};

