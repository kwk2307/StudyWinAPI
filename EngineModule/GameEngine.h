#pragma once
class GameEngine
{
public: 
	GameEngine() = default;
public:
	bool Init(std::string& SceneName);
	bool IsInitailzed() { return _IsInitialized; }

	const std::vector<std::unique_ptr<Object>>& GetScene() const { return _Scene; }
private:

public:

private:
	bool _IsInitialized;

	std::vector<std::unique_ptr<Object>> _Scene;
	std::string _SceneName;

	SceneMng SceneMng;

};

