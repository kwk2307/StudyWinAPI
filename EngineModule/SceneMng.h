#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	const std::vector<std::unique_ptr<Object>>& GetCurrentScene() const { return _Scene; }

	const std::unique_ptr<Camera>& GetCamera() const { return _Camera; }
	const std::unique_ptr<Player>& GetPlayer() const { return _Player; }

	bool LoadScene(std::string SceneName);

private:
	// 여러개의 씬을 담아 둘 벡터
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// 오브젝트를 로드해서 넣어놓을 벡터 
	std::vector<std::unique_ptr<Object>> _Scene;
	std::string _CurrentSceneName = "StartScene";

	std::unique_ptr<Camera> _Camera;
	std::unique_ptr<Player> _Player;
};