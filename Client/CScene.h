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
	void finalupdate();
	void render(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	const vector<CObject*>& GetGroupObject(ObjectType _eType) { 
		return m_VecObjects[(UINT)_eType]; 
	}

public:
	void AddObject(CObject* _pObj, ObjectType _eType){m_VecObjects[(UINT)_eType].push_back(_pObj);}
		
public:
	CScene();
	// Manager에서 관리할 때 부모 클래스릍 통해 관리 되는데 
	// 소멸자를 실행 시켜 줄 때 부모 클래스의 소멸자만 호출 되기때문에
	// virtual로 만들어 자식 클래스의 소멸자를 호출 시켜줘야함
	virtual ~CScene();

};

