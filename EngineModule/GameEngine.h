#pragma once

class GameEngine
{
public:
	GameEngine() = default;

public:
	bool Init();
	bool IsInitailzed() { return _IsInitialized; }

// 함수에서의 const 

// 1. 매개변수 자료형에 const : 매개변수 를 수정할 수 없게됨
// 2. 함수 뒤에 const : const 맴버 함수로 만들어줌 이 함수는 객체의 맴버 변수를 수정할 수 없게 됨 const 객체는 이 함수만을 호출 할 수 있음 
// 3. 리턴에서의 const : 리턴이 const 객체가 됨
	SceneMng& GetSceneMng() { return _SceneMng; }
	
	Mesh& GetMesh(const std::size_t& InMeshKey) const { return *_Meshes.at(InMeshKey).get(); }

private:
	bool _IsInitialized = false;
	SceneMng _SceneMng;

	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
	//std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;

};



