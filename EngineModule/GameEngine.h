#pragma once

class GameEngine
{
public:
	GameEngine() = default;

public:
	bool Init();
	bool IsInitailzed() { return _IsInitialized; }

// �Լ������� const 

// 1. �Ű����� �ڷ����� const : �Ű����� �� ������ �� ���Ե�
// 2. �Լ� �ڿ� const : const �ɹ� �Լ��� ������� �� �Լ��� ��ü�� �ɹ� ������ ������ �� ���� �� const ��ü�� �� �Լ����� ȣ�� �� �� ���� 
// 3. ���Ͽ����� const : ������ const ��ü�� ��
	SceneMng& GetSceneMng() { return _SceneMng; }
	
	Mesh& GetMesh(const std::size_t& InMeshKey) const { return *_Meshes.at(InMeshKey).get(); }

private:
	bool _IsInitialized = false;
	SceneMng _SceneMng;

	std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
	//std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;

};



