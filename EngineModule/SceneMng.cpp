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

	ObjectInfo Player;
	Player.name = "player";
	Player.type = ObjectType::Player;
	Player.MeshKey = std::hash<std::string>()("M_Plane");

	Player.transform = TransformComponent(Vector3(0, 0, 0), Rotator(0.f, 0.f, 0.f), Vector3(1, 1, 1));
	startScene.get()->AddObject(Player);

	ObjectInfo Camera;
	Camera.name = "camera";
	Camera.type = ObjectType::Camera;
	startScene.get()->AddObject(Camera);

	_vecScene.push_back(std::move(startScene));

	return LoadScene("StartScene");
}

Mesh& SceneMng::CreateMesh(const std::size_t& Inkey)
{
	auto meshPtr = std::make_unique<Mesh>();
	_Meshes.insert({ Inkey,std::move(meshPtr) });

	return *_Meshes.at(Inkey).get();
}


bool SceneMng::LoadScene(std::string SceneName)
{
	std::size_t targetHash = std::hash<std::string>()(SceneName);
	const auto it = std::lower_bound(_vecScene.begin(), _vecScene.end(), targetHash, SceneCompare());

	Scene Scene = (it != _vecScene.end()) ? *(*it).get() : Scene::Invalid;
	if (Scene == Scene::Invalid) {
		return false;
	}

	_CurrentSceneName = SceneName;
	//�������� ���� �ʱ�ȭ 
	_Scene.clear();
	
	for (auto it = Scene.GetInfo().begin(); it != Scene.GetInfo().end(); ++it) {
		const ObjectInfo& objectinfo = (*it);
		switch (objectinfo.type)
		{
		case ObjectType::Default: 
		{
			_Scene.push_back(std::move(std::make_unique<Object>(objectinfo)));
			break;
		}
		case ObjectType::Camera:
		{
			std::unique_ptr<Camera> CameraPtr = std::make_unique<Camera>(objectinfo);
			_Camera = CameraPtr.get();
			_Scene.push_back(std::move(CameraPtr));
			break;
		}
		case ObjectType::Player:
		{
			std::unique_ptr<Player> PlayerPtr = std::make_unique<Player>(objectinfo);
			_Player = PlayerPtr.get();
			_Scene.push_back(std::move(PlayerPtr));
			break;
		}
		default:
			break;
		}
	}
	return true;
}

