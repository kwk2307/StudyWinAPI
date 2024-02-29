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

	Camera& GetCamera() { return *_Camera; }
	Player& GetPlayer() { return *_Player; }

	bool LoadScene(std::string SceneName);

private:
	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// ������Ʈ�� �ε��ؼ� �־���� ���� 
	std::vector<std::unique_ptr<Object>> _Scene;
	// �޽��� ���� Hash��
	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;

	std::string _CurrentSceneName = "StartScene";
	
	Camera* _Camera;
	Player* _Player;
};