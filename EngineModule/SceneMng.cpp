#include "Precompiled.h"

struct SceneCompare
{
	bool operator()(const std::unique_ptr<Scene>& lhs, std::size_t rhs)
	{
		return lhs->GetHash() < rhs;
	}
};

bool SceneMng::Init(const CollisionMngInterface* InCollisionMng)
{
	_CollisionMng = InCollisionMng;

	std::unique_ptr<Scene> startScene = std::make_unique<Scene>("StartScene");

	Mesh& PlayerMesh = CreateMesh(std::hash<std::string>()("M_PlayerPlane"));

	std::vector<size_t> vec_Indices = { 0,1,2,0,2,3 };
	PlayerMesh.GetIndices().assign(vec_Indices.begin(), vec_Indices.end());

	std::vector<Vector3> vec_Vertices = {
		Vector3(-35.f,-27.f,0.f),
		Vector3(35.f,-27.f,0.f),
		Vector3(35.f,27.f,0.f),
		Vector3(-35.f,27.f,0.f)
	};
	PlayerMesh.GetVertices().assign(vec_Vertices.begin(), vec_Vertices.end());
	// 가로 35 세로 27
	std::vector<Vector2> vec_UV = {
		Vector2(36.f / 491.f,27.f / 346.f),
		Vector2(70.f / 491.f,27.f / 346.f),
		Vector2(70.f / 491.f,1.f / 346.f),
		Vector2(36.f / 491.f,1.f / 346.f),
	};
	PlayerMesh.GetUVs().assign(vec_UV.begin(), vec_UV.end());

	Texture& PlayerTexture = CreateTexture(std::hash<std::string>()("T_Player"), "C:\\Users\\User\\Documents\\GitHub\\StudyWinAPI\\Resource\\Player.png");

	ObjectInfo Player;
	Player.name = "player";
	Player.type = ObjectType::Player;
	Player.transform = TransformComponent(Vector3(0.f, 0.f, 0.f), Rotator(0.f, 0.f, 0.f), Vector3(1, 1, 1));
	Player.Mesh = "M_PlayerPlane";
	Player.Texture = "T_Player";

	Player.IsCollision = true;
	Player.ColliderMesh = "M_PlayerPlane";

	startScene.get()->AddObject(Player);

	ObjectInfo Camera;
	Camera.name = "camera";
	Camera.type = ObjectType::Camera;
	startScene.get()->AddObject(Camera);

	ObjectInfo Block;
	Block.name = "block";
	Block.type = ObjectType::Block;
	Block.transform = TransformComponent(Vector3(0, -200, 0), Rotator(0.f, 0.f, 0.f), Vector3(10, 10, 1));

	Mesh& BlockMesh = CreateMesh(std::hash<std::string>()("M_Block"));

	std::vector<size_t> vec_Indices2 = { 0,1,2,0,2,3 };
	BlockMesh.GetIndices().assign(vec_Indices2.begin(), vec_Indices2.end());

	std::vector<Vector3> vec_Vertices2 = {
		Vector3(0.f,0.f,0.f),
		Vector3(1.f,0.f,0.f),
		Vector3(1.f,1.f,0.f),
		Vector3(0.f,1.f,0.f)
	};
	BlockMesh.GetVertices().assign(vec_Vertices2.begin(), vec_Vertices2.end());

	std::vector<Vector2> vec_UV2 = {
		Vector2(0.f,1.f),
		Vector2(1.f,1.f),
		Vector2(1.f,0.f),
		Vector2(0.f,0.f),
	};
	BlockMesh.GetUVs().assign(vec_UV2.begin(), vec_UV2.end());

	Texture& BlockTexture = CreateTexture(std::hash<std::string>()("T_Block"), Color::Green);

	Block.Mesh = "M_Block";
	Block.Texture = "T_Block";

	startScene.get()->AddObject(Block);

	_Scenes.push_back(std::move(startScene));

	return LoadScene("StartScene");
}

void SceneMng::SetScreenSize(const ScreenPoint& InScreen)
{
	return void();
}

Mesh& SceneMng::CreateMesh(const std::size_t& Inkey)
{
	auto meshPtr = std::make_unique<Mesh>();
	_Meshes.insert({ Inkey,std::move(meshPtr) });

	return *_Meshes.at(Inkey).get();
}

Mesh& SceneMng::CreateMesh(std::string InName, std::vector<Vector3> InVertices, std::vector<size_t> Indices, std::vector<Vector2> InUVs)
{
	auto meshPtr = std::make_unique<Mesh>(InName,InVertices, Indices, InUVs);

	std::size_t key = std::hash<std::string>()(InName);

	_Meshes.insert({ key,std::move(meshPtr) });

	return *_Meshes.at(key).get();

}

Texture& SceneMng::CreateTexture(const std::size_t& Inkey, const std::string& InAddress)
{
	auto meshPtr = std::make_unique<Texture>(InAddress);
	_Textures.insert({ Inkey,std::move(meshPtr) });

	return *_Textures.at(Inkey).get();

}

Texture& SceneMng::CreateTexture(const std::size_t& Inkey, const Color& Incolor)
{
	auto meshPtr = std::make_unique<Texture>(Incolor);
	_Textures.insert({ Inkey,std::move(meshPtr) });

	return *_Textures.at(Inkey).get();

}

bool SceneMng::LoadScene(std::string SceneName)
{
	std::size_t targetHash = std::hash<std::string>()(SceneName);
	const auto it = std::lower_bound(_Scenes.begin(), _Scenes.end(), targetHash, SceneCompare());

	Scene Scene = (it != _Scenes.end()) ? *(*it).get() : Scene::Invalid;
	if (Scene == Scene::Invalid) {
		return false;
	}

	_CurrentSceneName = SceneName;
	// 오브젝터 벡터 초기화 
	// _Objects.clear();
	
	for (auto it = Scene.GetInfo().begin(); it != Scene.GetInfo().end(); ++it) {
		const ObjectInfo& objectinfo = (*it);
		switch (objectinfo.type)
		{
		case ObjectType::Default: 
		{
			_Objects[(UINT)ObjectType::Default].push_back(std::make_shared<Object>(objectinfo));
			break;
		}
		case ObjectType::Block:
		{
			_Objects[(UINT)ObjectType::Block].push_back(std::make_shared<Object>(objectinfo));
			break;
		}
		case ObjectType::Camera:
		{
			std::shared_ptr<Camera> CameraPtr = std::make_shared<Camera>(objectinfo);
			_MainCamera = CameraPtr.get();
			_Objects[(UINT)ObjectType::Camera].push_back(CameraPtr);
			break;
		}
		case ObjectType::Player:
		{
			std::shared_ptr<Player> PlayerPtr = std::make_shared<Player>(objectinfo);
			_MainPlayer = PlayerPtr.get();
			_Objects[(UINT)ObjectType::Player].push_back(PlayerPtr);
			break;
		}
		default:
			break;
		}
	}
	return true;
}

void SceneMng::Update(float InDeltaSeconds)
{
	for (UINT Type = 0; Type < (UINT)ObjectType::End; ++Type) {
		for (auto it = GetCurrentScene(Type).begin();
			it != GetCurrentScene(Type).end(); ++it) {
			Object& object = *(*it);

			object.Update(InDeltaSeconds);
		}
	}
}

