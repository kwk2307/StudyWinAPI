#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _ptObj, ObjectType _eType)
{
	CEventMgr::GetInstance()->AddEvent(Event{ EventType::CREATEOBJECT, (DWORD_PTR)_ptObj, (DWORD_PTR)_eType});
}

void DeleteObject(CObject* _ptObj)
{
	CEventMgr::GetInstance()->AddEvent(Event{ EventType::DELETEOBJECT, (DWORD_PTR)_ptObj});
}
