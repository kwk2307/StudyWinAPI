#pragma once

class GameEngine
{
public:
	GameEngine() = default;

public:
	bool Init(std::string& InName);
	bool IsInitailzed() { return _IsInitialized; }

	//���� �����ڰ� ���Ͼ�� �����ڷμ� �Ѱ��ָ� ��
	SceneMng& GetSceneMng() { return _SceneMng; }
private:

public:

private:
	bool _IsInitialized = false;
	SceneMng _SceneMng;
};

