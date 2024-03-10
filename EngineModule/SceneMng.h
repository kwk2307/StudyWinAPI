#pragma once
class SceneMng {

public:
	SceneMng() = default;
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }

	const std::vector<std::shared_ptr<Object>>& GetCurrentScene(UINT InType) const{ 
		return _Objects[InType];
	}

	Mesh& CreateMesh(const std::size_t& Inkey);
	Texture& CreateTexture(const std::size_t& Inkey, const std::string& InAddress);

	Mesh& GetMesh(const std::size_t& InMeshKey) const { return *_Meshes.at(InMeshKey).get(); }
	Texture& GetTexture(const std::size_t InTextureKey) const { return *_Textures.at(InTextureKey).get(); }

	Camera& GetCamera() { return *_MainCamera; }
	Player& GetPlayer() { return *_MainPlayer; }

	bool LoadScene(std::string SceneName);

	void Update(float InDeltaSeconds);

private:
	// 여러개의 씬을 담아 둘 벡터
	std::vector<std::unique_ptr<Scene>> _Scenes;

private:
	// 오브젝트를 로드해서 넣어놓을 벡터 
	std::vector<std::shared_ptr<Object>> _Objects[(UINT)ObjectType::End];

	// 메쉬를 담어둘 unordered_map 
	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
	
	// 텍스쳐를 담아둘 unordered_map 
	std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;

	std::string _CurrentSceneName = "StartScene";
	
	Camera* _MainCamera;
	Player* _MainPlayer;
};