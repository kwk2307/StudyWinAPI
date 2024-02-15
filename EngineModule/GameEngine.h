#pragma once

class GameEngine
{
public:
	GameEngine() = default;

public:
	bool Init(std::string& InName);
	bool IsInitailzed() { return _IsInitialized; }

	//복사 생성자가 안일어나게 참조자로서 넘겨주면 됨
	SceneMng& GetSceneMng() { return _SceneMng; }
private:

public:

private:
	bool _IsInitialized = false;
	SceneMng _SceneMng;
};

