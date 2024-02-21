#pragma once
class SceneMng {

public:
	SceneMng();
public:
	bool Init();

	const std::string& GetCurrentSceneName() const { return _CurrentSceneName; }
	const std::vector<std::unique_ptr<Object>>& GetCurrentScene() const { return _Scene; }

	const std::unique_ptr<Camera>& GetCamera() const { return _Camera; }
	const std::unique_ptr<Player>& GetPlayer() const { return _Player; }

	bool LoadScene(std::string SceneName);

private:
	// �������� ���� ��� �� ����
	std::vector<std::unique_ptr<Scene>> _vecScene;

private:
	// ������Ʈ�� �ε��ؼ� �־���� ���� 
	std::vector<std::unique_ptr<Object>> _Scene;
	std::string _CurrentSceneName = "StartScene";

	std::unique_ptr<Camera> _Camera;
	std::unique_ptr<Player> _Player;
};