#pragma once

class GameEngine
{
public:
	// 기본생성자를 사용하겠다.
	GameEngine() = default;

public:
	bool Init();
	bool IsInitailzed() { return _IsInitialized; }

	SceneMng& GetSceneMng() { return _SceneMng; }
	CollisionMng& GetCollisionMng() { return _CollisionMng; }

	void Update(float InDeltaSeconds);
public:


private:
	bool _IsInitialized = false;
	
    SceneMng _SceneMng;
	CollisionMng _CollisionMng;
};



