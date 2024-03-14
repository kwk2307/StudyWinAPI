#pragma once
class SceneMng :
	public SceneMngInterface
{

public:
	SceneMng() = default;
public:
	bool Init(CollisionMngInterface* InCollisionMng);

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }

	virtual const std::vector<std::shared_ptr<Object>>& GetCurrentScene(UINT InType) const override{ 
		return _Objects[InType];
	}

	Mesh& CreateMesh(const std::size_t& Inkey);
	Texture& CreateTexture(const std::size_t& Inkey, const std::string& InAddress);
	Texture& CreateTexture(const std::size_t& Inkey, const Color& Incolor);

	virtual Mesh& GetMesh(const std::size_t& InMeshKey) const override { return *_Meshes.at(InMeshKey).get(); }
	virtual Texture& GetTexture(const std::size_t InTextureKey) const override { return *_Textures.at(InTextureKey).get(); }

	virtual Camera& GetCamera() override { return *_MainCamera; }
	virtual Player& GetPlayer() override { return *_MainPlayer; }

	virtual bool LoadScene(std::string SceneName) override;

	virtual void Update(float InDeltaSeconds) override;

private:
	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _Scenes;

private:
	// ������Ʈ�� �ε��ؼ� �־���� ���� 
	std::vector<std::shared_ptr<Object>> _Objects[(UINT)ObjectType::End];
	 
	// �޽��� ���� unordered_map 
	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
	
	// �ؽ��ĸ� ��Ƶ� unordered_map 
	std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;

	std::string _CurrentSceneName = "StartScene";
	
	CollisionMngInterface* _CollisionMng;

	Camera* _MainCamera = nullptr;
	Player* _MainPlayer = nullptr;
};