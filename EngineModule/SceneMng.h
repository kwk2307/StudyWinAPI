#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	bool LoadScene(std::string SceneName);
	std::unique_ptr<Object> MakeObject(const ObjectInfo& Info);
	void Update(float InDeltaSecond);

private:

public:

private:

	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _vecScene;

	// ������Ʈ�� �ε��ؼ� �־���� ���� 
	std::vector<std::unique_ptr<Object>> _Scene;

	std::string _CurrentSceneName = "StartScene";
};