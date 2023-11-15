#include "pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CObject.h"
#include "CUI.h"


CUIMgr::CUIMgr():
	m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr() {

}

void CUIMgr::update()
{
	if (KEYCHKCK_TAP(KEY::LBUTTON)) {
		m_pFocusedUI = FindFocusedUI();
	}

	if (m_pFocusedUI != nullptr) {
		CUI* pTagertUI = GetTargetedUI(m_pFocusedUI);
		ClickEvent(pTagertUI);
	}
}

void CUIMgr::ClickEvent(CUI* _pUI)
{
	if (_pUI->GetOnMouse() && _pUI->GetClickable()) {
		if (KEYCHKCK_TAP(KEY::LBUTTON)) {
			_pUI->SetState(UIState::Clicked);
			_pUI->OnMouseTap();
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

CUI* CUIMgr::FindFocusedUI()
{
	CUI* pFocusedUI = nullptr;

	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurrentScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	vector<CObject*>::iterator Targetiter = vecUI.end();

	// 현재 마우스가 클릭 됐을 때 
	for (; iter != vecUI.end(); ++iter) {
		CUI* pUI = dynamic_cast<CUI*>(*iter);
		if (pUI->GetOnMouse() && pUI->GetClickable()) {
			Targetiter = iter;
		}
	}

	if (Targetiter != vecUI.end()) {
		pFocusedUI = dynamic_cast<CUI*>(*Targetiter);
		vecUI.erase(Targetiter);
		vecUI.push_back(pFocusedUI);
	}

	return pFocusedUI;
}
