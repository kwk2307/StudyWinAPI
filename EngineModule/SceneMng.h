#pragma once
class SceneMng {
public:
	SceneMng() = default;
public:
	void Init();

	//bool LoadScene(std::string& SceneName);
	//const std::vector<std::unique_ptr<Object>>& GetScene() const { return _Scene; }
	const std::string& GetSceneName() const { return _SceneName; }

	void Update(float InDeltaSeconds);

private:

public:

private:
	// 여러개의 씬을 담아 둘 벡터
	// std::vector<std::unique_ptr<Scene>> _vecScene;

	// LoadScene에 의해서 선택된 Scene을 담아둘 변수 
	//std::vector<std::unique_ptr<Object>> _Scene;
	
	// 필요한 리소스도 Scene이 가지고 있음

	std::string _SceneName;
};