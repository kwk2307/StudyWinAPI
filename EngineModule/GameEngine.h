#pragma once
class GameEngine
{
public:
	bool Init();
	bool IsInitailzed() { return _IsInitialized; }

private:
	bool _IsInitialized;
};

