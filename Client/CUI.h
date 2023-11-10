#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecUI;
    CUI* m_pParentUI;

    Vec2 m_vOffset;

public:
    void SetChild(CUI* _pUI);
    void SetParent(CUI* _pUI) { m_pParentUI = _pUI;}

    Vec2 GetOffset() { return m_vOffset; }
    void SetOffset(Vec2 _vOffset) { m_vOffset = _vOffset; }
public:
    void finalEvnet();

public:
    virtual void update();
    virtual void render(HDC _dc);
public:
    CUI();
    ~CUI();
};

