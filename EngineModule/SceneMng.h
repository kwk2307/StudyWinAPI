#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	bool LoadScene(std::string SceneName);
	std::unique_ptr<Object> MakeObject(const ObjectInfo& Info);
	void Update(float InDeltaSecond);

private:

public:

private:

	// 여러개의 씬을 담아 둘 벡터
	std::vector<std::unique_ptr<Scene>> _vecScene;

	// 오브젝트를 로드해서 넣어놓을 벡터 
	std::vector<std::unique_ptr<Object>> _Scene;

	std::string _CurrentSceneName = "StartScene";
};