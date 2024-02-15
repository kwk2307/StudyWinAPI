#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	// bool LoadScene(std::string& SceneName);
	// const Scene& GetScene() const;
	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }

private:

public:

private:

	// 여러개의 씬을 담아 둘 벡터
	std::vector<std::unique_ptr<Scene>> _VecScene;

	std::string _CurrentSceneName;
};