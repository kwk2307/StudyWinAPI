#pragma once

class CObject;

class CScene
{
private:
	vector<CObject*> m_VecObjects[(UINT)ObjectType::END];
	wstring m_strName;

	vector<CObject*>::iterator iter;
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	const vector<CObject*>& GetGroupObject(ObjectType _eType) { 
		return m_VecObjects[(UINT)_eType]; 
	}


protected:
	void AddObject(CObject* _pObj, ObjectType _eType){m_VecObjects[(UINT)_eType].push_back(_pObj);}
	
	void DeleteType(ObjectType _eType);
	void DeleteAll();

public:
	CScene();
	// Manager���� ������ �� �θ� Ŭ������ ���� ���� �Ǵµ� 
	// �Ҹ��ڸ� ���� ���� �� �� �θ� Ŭ������ �Ҹ��ڸ� ȣ�� �Ǳ⶧����
	// virtual�� ����� �ڽ� Ŭ������ �Ҹ��ڸ� ȣ�� ���������
	virtual ~CScene();

	friend class CEventMgr;
};

