#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	//bool LoadScene(std::string& SceneName);
	//const std::vector<std::unique_ptr<Object>>& GetScene() const { return _Scene; }
	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }

	void Update(float InDeltaSeconds);

private:

public:

private:
	
	// std::unique_ptr<Scene> _StartScene = std::make_unique<Scene>("StartScene");
	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _VecScene;

	std::string _CurrentSceneName;
};