#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"
#include "CStage01.h"

CSceneMgr::CSceneMgr() :
	m_ArrScenes{},
	m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr() 
{
	for (int i = 0; i < (INT)SceneType::END; ++i) {
		if (m_ArrScenes[i] != nullptr) {
			delete m_ArrScenes[i];
		}
	}
}

void CSceneMgr::init()
{
	m_ArrScenes[(UINT)SceneType::STARTSCENE] = new CScene_Start;
	m_ArrScenes[(UINT)SceneType::STARTSCENE]->SetName(L"StartScene");
	
	m_ArrScenes[(UINT)SceneType::STAGE01] = new CStage01;
	//m_ArrScenes[(UINT)SceneType::STAGE02] = new CSTAGE02;

	m_pCurScene = m_ArrScenes[(UINT)SceneType::STARTSCENE];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

CScene* CSceneMgr::GetCurrentScene()
{
	return m_pCurScene;
}

void CSceneMgr::ChangeScene(SceneType _eType)
{
	m_pCurScene->Exit();

	m_pCurScene = m_ArrScenes[(UINT)_eType];

	m_pCurScene->Enter();
}

