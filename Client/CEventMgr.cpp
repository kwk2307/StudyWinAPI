#include "pch.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"
CEventMgr::CEventMgr() {

}

CEventMgr::~CEventMgr() {

}


void CEventMgr::init() {

}

void CEventMgr::update()
{
	for (size_t i = 0; i < m_vEvent.size(); ++i) {
		
		switch (m_vEvent[i].eType)
		{
		case EventType::SCENECHANGE:
			break;
		case EventType::CREATEOBJECT:
		{
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject((CObject*)m_vEvent[i].WParam, (ObjectType)m_vEvent[i].LParam);
			break;
		}
		case EventType::DELETEOBJECT:
		{
			CObject* ptObj = (CObject*)m_vEvent[i].WParam;
			ptObj->SetDead(true);
			break;
		}
		case EventType::END:
			break;
		default:
			break;
		}
	}
	//이벤트 대기열 비워줌
	m_vEvent.clear();
}
