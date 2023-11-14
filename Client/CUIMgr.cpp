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
	
	static queue<CUI*> queContainer;
	static vector<CUI*> vecContainer;

	for (int i = 0; i < vecUI.size(); ++i) {
		CUI* pUI = dynamic_cast<CUI*>(vecUI[i]);
		assert(pUI);

		queContainer.push(pUI);
		while (!queContainer.empty()) {
			const vector<CUI*>& vecChild = queContainer.front()->GetChild();
			for (int i = 0; i < vecChild.size(); ++i) {
				queContainer.push(vecChild[i]);
			}
			vecContainer.push_back(queContainer.front());
			queContainer.pop();
		}

		for (int j = vecContainer.size() - 1; j >= 0; --j) {
			if (ClickEvent(vecContainer[j])) {
				break;
			}
			
		}
		vecContainer.clear();
	}
}

bool CUIMgr::ClickEvent(CObject* _object)
{
	CUI* pUI = dynamic_cast<CUI*>(_object);
	assert(pUI);

	Vec2 vPos = pUI->GetPos();
	Vec2 vScale = pUI->GetScale();

	Vec2 vMousPos = MOUSEPOS;

	bool bOnMouse = (
		vPos.x + (vScale.x / 2) > vMousPos.x &&
		vPos.x - (vScale.x / 2) < vMousPos.x &&
		vPos.y + (vScale.y / 2) > vMousPos.y &&
		vPos.y - (vScale.y / 2) < vMousPos.y);

	if (bOnMouse && pUI->GetClickable()) {
		if (KEYCHKCK_TAP(KEY::LBUTTON)) {
			pUI->SetState(UIState::Clicked);
		}
		else if (KEYCHKCK_HOLD(KEY::LBUTTON)) {
			pUI->SetState(UIState::Clicked);
		}
		else if (KEYCHKCK_AWAY(KEY::LBUTTON)) {
			pUI->SetState(UIState::Hover);
			//OnButtonClick();
		}
		else {
			pUI->SetState(UIState::Hover);
		}
		return true;
	}
	else {
		pUI->SetState(UIState::None);
		return false;
	}
}
