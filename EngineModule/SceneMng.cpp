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
	std::unique_ptr<Scene> startScene(new Scene("StartScene"));
	_VecScene.push_back(std::move(startScene));

	return true;
}

//bool SceneMng::LoadScene(std::string& SceneName)
//{
//	std::size_t targetHash = std::hash<std::string>()(SceneName);
//	const auto it = std::lower_bound(_vecScene.begin(), _vecScene.end(), targetHash, SceneCompare());
//
//	Scene Scene = (it != _vecScene.end()) ? *(*it).get() : Scene::Invalid;
//	Invaild �� �� Fail ���ִ� ����ó�� �ʿ�
//	if( )
//
//	_Scene = Scene.GetObjects();
//
//	return false;
//}

void SceneMng::Update(float InDeltaSeconds)
{
	for (auto it = _VecScene.begin(); it != _VecScene.end(); ++it) {
		Scene& scene = *(*it);
		scene.Update(InDeltaSeconds);

	}
}
