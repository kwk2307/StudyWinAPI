#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecUI;
    CUI* m_pParentUI;

    Vec2 m_vOffset;
    bool m_bClickable;

    UIState m_eState;

public:
    void SetChild(CUI* _pUI) {
        m_vecUI.push_back(_pUI);
        _pUI->m_pParentUI = this;
    }

    Vec2 GetOffset() { return m_vOffset; }
    void SetOffset(Vec2 _vOffset) { m_vOffset = _vOffset; }

    bool GetClickable() { return m_bClickable; }
    void SetClickable(bool _enable) { m_bClickable = _enable; }

    UIState GetState() { return m_eState; }
    void SetState(UIState _state) { m_eState = _state; }

    const vector<CUI*>& GetChild() { return m_vecUI; }

public:
    void finalEvnet();

public:
    virtual void update();
    virtual void render(HDC _dc);
public:
    CUI();
    ~CUI();
};

