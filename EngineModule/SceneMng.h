#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	const std::vector<std::unique_ptr<Object>>GetCurrentScene() const { return _Scene; }

	const Camera GetMainCamera() const {return _MainCamera;}

	bool LoadScene(std::string SceneName);
	std::unique_ptr<Object> MakeObject(const ObjectInfo& Info);

private:
	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// ������Ʈ�� �ε��ؼ� �־���� ���� 
	std::vector<std::unique_ptr<Object>> _Scene;
	std::string _CurrentSceneName = "StartScene";

	Camera _MainCamera;
};