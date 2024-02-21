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

	ObjectInfo Player;
	Player.name = "player";
	Player.type = ObjectType::Player;

	startScene.get()->AddObject(Player);

	ObjectInfo Camera;
	Camera.name = "camera";
	Camera.type = ObjectType::Camera;

	startScene.get()->AddObject(Camera);

	_vecScene.push_back(std::move(startScene));

	return LoadScene("StartScene");
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
	//오브젝터 벡터 초기화 
	_Scene.clear();
	
	for (auto it = Scene.GetInfo().begin(); it != Scene.GetInfo().end(); ++it) {
		
		//값 복사가 일어나지 않게 참조자로 받아옴
		const ObjectInfo& objectinfo = (*it);
		switch (objectinfo.type)
		{
		case ObjectType::Default:
			_Scene.push_back(std::move(std::make_unique<Object>(objectinfo)));
			break;
		case ObjectType::Camera:

			_Camera = std::make_unique<Camera>(objectinfo);
			break;
		case ObjectType::Player:

			_Player = std::make_unique<Player>(objectinfo);
			break;
		default:
			break;
		}
	}
	return true;
}

