#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	const std::vector<std::unique_ptr<Object>>& GetCurrentScene() const { return _Scene; }

	Mesh& CreateMesh(const std::size_t& Inkey);
	Texture& CreateTexture(const std::size_t& Inkey, const std::string& InAddress);

	Mesh& GetMesh(const std::size_t& InMeshKey) const { return *_Meshes.at(InMeshKey).get(); }
	Texture& GetTexture(const std::size_t InTextureKey) const { return *_Textures.at(InTextureKey).get(); }

	Camera& GetCamera() { return *_Camera; }
	Player& GetPlayer() { return *_Player; }

	bool LoadScene(std::string SceneName);

private:
	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// ������Ʈ�� �ε��ؼ� �־���� ���� 
	std::vector<std::unique_ptr<Object>> _Scene;
	// �޽��� ���� unordered_map 
	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
	// �ؽ��ĸ� ��Ƶ� unordered_map 
	std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;

	std::string _CurrentSceneName = "StartScene";
	
	Camera* _Camera;
	Player* _Player;
};