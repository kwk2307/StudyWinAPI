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
	
private:
	bool _IsInitialized = false;
	
	SceneMng _SceneMng;

};



