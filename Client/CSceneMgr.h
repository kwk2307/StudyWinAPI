#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

private:
	CScene* m_ArrScenes[(UINT)SceneType::END];//¸ðµç ¾À ¸ñ·Ï
	CScene* m_pCurScene;

public:
	void init();

	void update();
	void render(HDC _dc);
	
	CScene* GetCurrentScene();
private:
	void ChangeScene(SceneType _eType);

	friend class CEventMgr;
};

