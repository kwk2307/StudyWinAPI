#include "Precomplied.h"

struct SceneCompare
{
	bool operator()(const std::unique_ptr<Scene>& lhs, std::size_t rhs)
	{
		return lhs->GetHash() < rhs;
	}
};
//void SceneMng::init() {
//	std::unique_ptr<Scene> startScene(new Scene("StartScene"));
//	_vecScene.push_back(startScene);
//}
//
//bool SceneMng::LoadScene(std::string& SceneName)
//{
//	std::size_t targetHash = std::hash<std::string>()(SceneName);
//	const auto it = std::lower_bound(_vecScene.begin(), _vecScene.end(), targetHash, SceneCompare());
//
//	Scene Scene = (it != _vecScene.end()) ? *(*it).get() : Scene::Invalid;
//	//Invaild 일 때 Fail 해주는 예외처리 필요
//	//if( )
//
//	//_Scene = Scene.GetObjects();
//
//	return false;
//}
//
//void SceneMng::Update(float InDeltaSeconds)
//{
//	for (auto it = _Scene.begin(); it != _Scene.end(); ++it) {
//		Object& Object = *(*it);
//		Object.Update(InDeltaSeconds);
//
//	}
//}
