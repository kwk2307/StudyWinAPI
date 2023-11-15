#include "pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CObject.h"
#include "CUI.h"


CUIMgr::CUIMgr() {

}

CUIMgr::~CUIMgr() {

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurrentScene();

	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(ObjectType::UI);

	for (int i = 0; i < vecUI.size(); ++i) {
		CUI* pParentUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pParentUI);

		CUI* pUI = GetTargetedUI(pParentUI);
		ClickEvent(pUI);
	}
}

bool CUIMgr::ClickEvent(CUI* _pUI)
{
	bool bResult = false;
	if (_pUI->GetOnMouse() && _pUI->GetClickable()) {
		if (KEYCHKCK_TAP(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Clicked);
			_pUI->OnMouseTap();
			bResult = true;
		}
		else if (KEYCHKCK_HOLD(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Clicked);
			_pUI->OnMouseHold();
		}
		else if (KEYCHKCK_AWAY(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Hover);
			_pUI->OnMouseAway();
		}
		else {
			//호버 상태가 된다고 포커싱이 뺏기진 않는다
			_pUI->SetState(UIState::Hover);
		}
	}

	return bResult;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	CUI* pTargetUI = _pParentUI;
	static queue<CUI*> que;
	que.push(_pParentUI);

	while (!que.empty()) {
		CUI* pUI = que.front();

		que.pop();

		if (pUI->GetOnMouse()) {
			pTargetUI = pUI;
			pTargetUI->SetState(UIState::None);
		}
		else {
			pUI->SetState(UIState::None);
		}

		const vector<CUI*>& vecChild = pUI->GetChild();
		for (size_t i = 0; i < vecChild.size(); ++i) {
			que.push(vecChild[i]);
		}
	}

	return pTargetUI;
}
