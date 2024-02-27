#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	const std::vector<std::unique_ptr<Object>>& GetCurrentScene() const { return _Scene; }

	Mesh& CreateMesh(const std::size_t& Inkey);
	Mesh& GetMesh(const std::size_t& InMeshKey) const { return *_Meshes.at(InMeshKey).get(); }

	const Camera& GetCamera() const { return *_Camera; }
	const Player& GetPlayer() const { return *_Player; }

	bool LoadScene(std::string SceneName);

private:
	// 여러개의 씬을 담아 둘 벡터
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// 오브젝트를 로드해서 넣어놓을 벡터 
	std::vector<std::unique_ptr<Object>> _Scene;
	// 메쉬를 담어둘 Hash맵
	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;

	std::string _CurrentSceneName = "StartScene";
	
	Camera* _Camera;
	Player* _Player;
};