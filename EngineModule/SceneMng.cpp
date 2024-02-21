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
		// 오브젝트 만드는 코드 

		const ObjectInfo& objectinfo = (*it);
		_Scene.push_back(std::move(MakeObject(objectinfo)));
	}

	return true;
}

std::unique_ptr<Object> SceneMng::MakeObject(const ObjectInfo& Info)
{
	// 생성 디자인 패턴을 고민 해봐야할듯?
	// 클래스가 하나 늘어날 때 마다 이 함수를 고치는 것은 너무 비효율적 
	
	switch (Info.type)
	{
	case ObjectType::Default:		
		break;
	case ObjectType::Camera:
		
		return std::make_unique<Camera>(Info);
		break;
	case ObjectType::Player:

		return std::make_unique<Player>(Info);
		break;
	default:
		break;
	}
}
