#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator():
    m_mAni{},
    m_pCurAnim(nullptr),
    m_pOwner(nullptr)
{
}

CAnimator::~CAnimator()
{
    Safe_Erase_Map(m_mAni);
}

CAnimator::CAnimator(const CAnimator& origin) :
    m_mAni{},
    m_pCurAnim(origin.m_pCurAnim),
    m_pOwner(nullptr)
{
    m_mAni = origin.m_mAni;
}

CAnimation* CAnimator::FindAnim(const wstring& _str)
{
    map<wstring, CAnimation*>::iterator iter = m_mAni.find(_str);
    
    if (iter != m_mAni.end()) {
        return iter->second;
    }

    return nullptr;
}

CAnimation* CAnimator::CreateAnim(const wstring& _str, CTexture* _pTex, Vec2 _vLT, Vec2 _vSize, UINT _cnt)
{
    CAnimation* pResultAnim = FindAnim(_str);
    if (pResultAnim != nullptr) {
        return pResultAnim;
    }

    CAnimation* pAnim = new CAnimation();
    pAnim->Create(_str, _pTex, _vLT, _vSize, _cnt);
    pAnim->SetAnimator(this);

    m_mAni.insert(make_pair(_str, pAnim));
    return pResultAnim;
}

void CAnimator::SetCurAnim(const wstring& _str)
{    
    CAnimation* pResultAnim = FindAnim(_str);
    if (pResultAnim != m_pCurAnim) {
        m_pCurAnim = pResultAnim;
    }
}

void CAnimator::update()
{
    m_pCurAnim->update();
}

void CAnimator::render(HDC _dc)
{
    m_pCurAnim->render(_dc);
}
