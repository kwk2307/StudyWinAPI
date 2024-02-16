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
	//�������� ���� �ʱ�ȭ 
	_Scene.clear();
	
	for (auto it = Scene.GetInfo().begin(); it != Scene.GetInfo().end(); ++it) {
		// ������Ʈ ����� �ڵ� 

		const ObjectInfo& objectinfo = (*it);
		_Scene.push_back(std::move(MakeObject(objectinfo)));
	}

	return true;
}

std::unique_ptr<Object> SceneMng::MakeObject(const ObjectInfo& Info)
{
	// ���� ������ ������ ���� �غ����ҵ�?
	// Ŭ������ �ϳ� �þ �� ���� �� �Լ��� ��ġ�� ���� �ʹ� ��ȿ���� 

	// 
	
	return std::unique_ptr<Object>();
}

void SceneMng::Update(float InDeltaSecond)
{
	for (auto it = _Scene.begin(); it != _Scene.end(); ++it) {
		Object& object = *(*it);

		object.Update(InDeltaSecond);
	}
}

