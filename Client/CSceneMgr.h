#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

private:
	CScene* m_ArrScenes[(UINT)SceneType::END];//��� �� ���
	CScene* m_CurScene;

public:
	void init();
	
	CScene* GetCurrentScene();
private:

};

