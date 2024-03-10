#include "Precompiled.h"

struct SceneCompare
{
	bool operator()(const std::unique_ptr<Scene>& lhs, std::size_t rhs)
	{
		return lhs->GetHash() < rhs;
	}
};

bool SceneMng::Init() {

	std::unique_ptr<Scene> startScene = std::make_unique<Scene>("StartScene");

	Mesh& Plane = CreateMesh(std::hash<std::string>()("M_Plane"));

	std::vector<size_t> vec_Indices = { 0,1,2,0,2,3 };
	Plane.GetIndices().assign(vec_Indices.begin(), vec_Indices.end());

	std::vector<Vector3> vec_Vertices = {
		Vector3(-100.f,-100.f,0.f),
		Vector3(100.f,-100.f,0.f),
		Vector3(100.f,100.f,0.f),
		Vector3(-100.f,100.f,0.f)
	};
	Plane.GetVertices().assign(vec_Vertices.begin(),vec_Vertices.end());

	std::vector<Vector2> vec_UV = {
		Vector2(35.f / 491.f,27.f / 346.f),
		Vector2(70.f / 491.f,27.f / 346.f),
		Vector2(70.f / 491.f,0.f),
		Vector2(35.f / 491.f,0.f),
	};
	Plane.GetUVs().assign(vec_UV.begin(), vec_UV.end());

	Texture& PlayerTexture = CreateTexture(std::hash<std::string>()("T_Player"),"C:\\Users\\User\\Documents\\GitHub\\StudyWinAPI\\Resource\\Player.png");

	ObjectInfo Player;
	Player.name = "player";
	Player.type = ObjectType::Player;
	Player.transform = TransformComponent(Vector3(0, 0, 0), Rotator(0.f, 0.f, 0.f), Vector3(1, 1, 1));
	Player.Mesh = "M_Plane";
	Player.Texture = "T_Player";

	startScene.get()->AddObject(Player);

	ObjectInfo Camera;
	Camera.name = "camera";
	Camera.type = ObjectType::Camera;
	startScene.get()->AddObject(Camera);

	_Scenes.push_back(std::move(startScene));

	return LoadScene("StartScene");
}

Mesh& SceneMng::CreateMesh(const std::size_t& Inkey)
{
	auto meshPtr = std::make_unique<Mesh>();
	_Meshes.insert({ Inkey,std::move(meshPtr) });

	return *_Meshes.at(Inkey).get();
}

Texture& SceneMng::CreateTexture(const std::size_t& Inkey, const std::string& InAddress)
{
	auto meshPtr = std::make_unique<Texture>(InAddress);
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
			_Objects[(UINT)ObjectType::Camera].push_back(PlayerPtr);
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

