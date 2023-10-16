#pragma once

class CObject;

class CScene
{
private:
	CObject* m_ArrObjects[(UINT)ObjectType::END];
	wstring m_strName;
public:

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render();

public:
	
	CScene();
	// Manager���� ������ �� �θ� Ŭ������ ���� ���� �Ǵµ� 
	// �Ҹ��ڸ� ���� ���� �� �� �θ� Ŭ������ �Ҹ��ڸ� ȣ�� �Ǳ⶧����
	// virtual�� ����� �ڽ� Ŭ������ �Ҹ��ڸ� ȣ�� ���������
	virtual ~CScene();

};

