#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
{
}

CAnimator::~CAnimator()
{
}

CAnimator::CAnimator(const CAnimator& origin)
{
}

CAnimation* CAnimator::FindAnim(const wstring& _str)
{
    map<wstring, CAnimation*>::iterator iter = m_mAni.find(_str);
    
    if (iter != m_mAni.end()) {
        return iter->second;
    }

    return nullptr;
}

CAnimation* CAnimator::CreateAnim(const wstring& _str, CRes* _pRes, Vec2 _vLT, Vec2 _vSize, UINT _cnt)
{
    CAnimation* pResultAnim = FindAnim(_str);
    if (pResultAnim != nullptr) {
        return pResultAnim;
    }

    CAnimation* pAnim = new CAnimation();


    return pResultAnim;
}
