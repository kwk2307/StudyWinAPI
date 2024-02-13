#pragma once
class SceneMng {
public:
	SceneMng() = default;
public:
	void Init();

	//bool LoadScene(std::string& SceneName);
	//const std::vector<std::unique_ptr<Object>>& GetScene() const { return _Scene; }
	const std::string& GetSceneName() const { return _SceneName; }

	void Update(float InDeltaSeconds);

private:

public:

private:
	// �������� ���� ��� �� ����
	// std::vector<std::unique_ptr<Scene>> _vecScene;

	// LoadScene�� ���ؼ� ���õ� Scene�� ��Ƶ� ���� 
	//std::vector<std::unique_ptr<Object>> _Scene;
	
	// �ʿ��� ���ҽ��� Scene�� ������ ����

	std::string _SceneName;
};