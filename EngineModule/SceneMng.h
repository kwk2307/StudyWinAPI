#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	const std::vector<std::unique_ptr<Object>>GetCurrentScene() const { return _Scene; }

	const Camera GetMainCamera() const {return _MainCamera;}

	bool LoadScene(std::string SceneName);
	std::unique_ptr<Object> MakeObject(const ObjectInfo& Info);

private:
	// 여러개의 씬을 담아 둘 벡터
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// 오브젝트를 로드해서 넣어놓을 벡터 
	std::vector<std::unique_ptr<Object>> _Scene;
	std::string _CurrentSceneName = "StartScene";

	Camera _MainCamera;
};