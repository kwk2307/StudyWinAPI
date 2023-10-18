#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_VecObjects[(UINT)ObjectType::END];
	wstring m_strName;		
public:

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	vector<CObject*> GetVecObject(ObjectType type) { return m_VecObjects[(UINT)type]; }

public:
	CScene();
	// Manager���� ������ �� �θ� Ŭ������ ���� ���� �Ǵµ� 
	// �Ҹ��ڸ� ���� ���� �� �� �θ� Ŭ������ �Ҹ��ڸ� ȣ�� �Ǳ⶧����
	// virtual�� ����� �ڽ� Ŭ������ �Ҹ��ڸ� ȣ�� ���������
	virtual ~CScene();

};

