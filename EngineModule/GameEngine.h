#pragma once

class GameEngine
{
public:
	GameEngine(SceneMng* InSceneMng, CollisionMng* InCollisionMng);

public:
	bool Init();
	bool IsInitailzed() { return _IsInitialized; }

	SceneMng& GetSceneMng() { return *_SceneMng; }
	CollisionMng& GetCollisionMng() { return *_CollisionMng; }

	void Update(float InDeltaSeconds);
public:


private:
	bool _IsInitialized = false;
	
    SceneMng* _SceneMng;
	CollisionMng* _CollisionMng;
};



