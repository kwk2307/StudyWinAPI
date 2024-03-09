#include "Precompiled.h"

struct SceneCompare
{
	bool operator()(const std::unique_ptr<Scene>& lhs, std::size_t rhs)
	{
		return lhs->GetHash() < rhs;
	}
};

SceneMng::SceneMng()
{

}

bool SceneMng::Init() {

	std::unique_ptr<Scene> startScene = std::make_unique<Scene>("StartScene");

	Mesh& Plane = CreateMesh(std::hash<std::string>()("M_Plane"));

	std::vector<size_t> vec_Indices = { 0,1,2,0,2,3 };
	Plane.GetIndices().assign(vec_Indices.begin(), vec_Indices.end());

	std::vector<Vector2> vec_Vertices = {
		Vector2(-100.f,-100.f),
		Vector2(100.f,-100.f),
		Vector2(100.f,100.f),
		Vector2(-100.f,100.f)
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
			_Objects[(UINT)ObjectType::Default].push_back(std::move(std::make_unique<Object>(objectinfo)));
			break;
		}
		case ObjectType::Camera:
		{
			std::unique_ptr<Camera> CameraPtr = std::make_unique<Camera>(objectinfo);
			_Camera = CameraPtr.get();
			_Objects[(UINT)ObjectType::Camera].push_back(std::move(CameraPtr));
			break;
		}
		case ObjectType::Player:
		{
			std::unique_ptr<Player> PlayerPtr = std::make_unique<Player>(objectinfo);
			_Player = PlayerPtr.get();
			_Objects[(UINT)ObjectType::Camera].push_back(std::move(PlayerPtr));
			break;
		}
		default:
			break;
		}
	}
	return true;
}

