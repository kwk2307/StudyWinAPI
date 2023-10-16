#include "pch.h"
#include "CSceneMgr.h"

CSceneMgr::CSceneMgr() :
	m_ArrScenes{}
{

}

CSceneMgr::~CSceneMgr() {

}

void CSceneMgr::init()
{
}

CScene* CSceneMgr::GetCurrentScene()
{
	return m_CurScene;
}
