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
		CUI* pUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pUI);

		pUI = GetTargetedUI(pUI);
		ClickEvent(pUI);
	}
}

void CUIMgr::ClickEvent(CUI* _pUI)
{
	if (_pUI->GetOnMouse() && _pUI->GetClickable()) {
		if (KEYCHKCK_TAP(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Clicked);
		}
		else if (KEYCHKCK_HOLD(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Clicked);
		}
		else if (KEYCHKCK_AWAY(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Hover);
			//OnButtonClick();
		}
		else {
			_pUI->SetState(UIState::Hover);
		}
	}
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
			pTargetUI->SetState(UIState::None);
			pTargetUI = pUI;
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
