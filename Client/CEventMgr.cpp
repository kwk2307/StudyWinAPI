#include "pch.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr() {

}

CEventMgr::~CEventMgr() {

}


void CEventMgr::update()
{
	m_vEvent;
	for (size_t i = 0; i < m_vEvent.size(); ++i) {
		
		switch (m_vEvent[i].eType)
		{
		SCENECHANGE:
			break;

		CREATEOBJECT:
			{
				CSceneMgr::GetInstance()->GetCurrentScene()->AddObject((CObject*) m_vEvent[i].LParam, (ObjectType)m_vEvent[i].WParam);
				break;
			}
		DELETEOBJECT:
			break;
		default:
			break;
		}
	}
}
