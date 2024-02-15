#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	// bool LoadScene(std::string& SceneName);
	// const Scene& GetScene() const;
	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }

private:

public:

private:

	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _VecScene;

	std::string _CurrentSceneName;
};