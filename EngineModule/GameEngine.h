#pragma once

class GameEngine
{
public:
	GameEngine(SceneMngInterface* InSceneMng, CollisionMngInterface* InCollisionMng);

public:
	bool Init(const ScreenPoint& InScreenSize);
	bool IsInitailzed() { return _IsInitialized; }

	SceneMngInterface& GetSceneMng() { return *_SceneMng; }
	CollisionMngInterface& GetCollisionMng() { return *_CollisionMng; }
	void Update(float InDeltaSeconds);
public:


private:
	bool _IsInitialized = false;
	
    SceneMngInterface* _SceneMng;
	CollisionMngInterface* _CollisionMng;
};



